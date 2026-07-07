#include <winsock2.h>
#include <ws2tcpip.h>
#include <algorithm>
#include <ctime>
#include <fstream>
#include <iostream>
#include <map>
#include <sstream>
#include <string>
#include <vector>

#pragma comment(lib, "ws2_32.lib")

using namespace std;

struct Task {
    int id;
    string title;
    string topic;
    string dueDate;
    string dueTime;
    int priority;
    bool needReview;
    bool completed;
    string createdDate;
    string completedDate;
    int estimatedMinutes;
    string note;
};

struct Recommendation {
    string title;
    string topic;
    int priority;
    int estimatedMinutes;
    string note;
};

const int PORT = 8090;
const string DATA_FILE = "study_tasks_v2.txt";
vector<Task> tasks;
int nextId = 1;

string todayDate() {
    time_t now = time(nullptr);
    tm* t = localtime(&now);
    char buffer[16];
    strftime(buffer, sizeof(buffer), "%Y-%m-%d", t);
    return buffer;
}

string cleanField(string value) {
    replace(value.begin(), value.end(), '|', '/');
    replace(value.begin(), value.end(), '\r', ' ');
    replace(value.begin(), value.end(), '\n', ' ');
    return value;
}

vector<string> split(const string& text, char delimiter) {
    vector<string> result;
    string item;
    stringstream ss(text);
    while (getline(ss, item, delimiter)) result.push_back(item);
    return result;
}

string jsonEscape(const string& value) {
    string result;
    for (char c : value) {
        if (c == '"') result += "\\\"";
        else if (c == '\\') result += "\\\\";
        else if (c == '\n') result += "\\n";
        else if (c == '\r') result += "";
        else result += c;
    }
    return result;
}

string urlDecode(const string& value) {
    string result;
    for (size_t i = 0; i < value.size(); ++i) {
        if (value[i] == '%' && i + 2 < value.size()) {
            string hex = value.substr(i + 1, 2);
            char ch = static_cast<char>(strtol(hex.c_str(), nullptr, 16));
            result += ch;
            i += 2;
        } else if (value[i] == '+') {
            result += ' ';
        } else {
            result += value[i];
        }
    }
    return result;
}

map<string, string> parseForm(const string& body) {
    map<string, string> data;
    vector<string> pairs = split(body, '&');
    for (const string& pairValue : pairs) {
        size_t pos = pairValue.find('=');
        if (pos == string::npos) continue;
        string key = urlDecode(pairValue.substr(0, pos));
        string value = urlDecode(pairValue.substr(pos + 1));
        data[key] = value;
    }
    return data;
}

bool parseDate(const string& date, int& y, int& m, int& d) {
    char c1 = 0;
    char c2 = 0;
    stringstream ss(date);
    return (ss >> y >> c1 >> m >> c2 >> d) && c1 == '-' && c2 == '-';
}

int dateToDays(const string& date) {
    int y = 0, m = 0, d = 0;
    if (!parseDate(date, y, m, d)) return 0;
    tm value{};
    value.tm_year = y - 1900;
    value.tm_mon = m - 1;
    value.tm_mday = d;
    value.tm_hour = 12;
    return static_cast<int>(mktime(&value) / 86400);
}

bool validDate(const string& date) {
    int y = 0, m = 0, d = 0;
    if (!parseDate(date, y, m, d)) return false;
    if (y < 1900 || m < 1 || m > 12 || d < 1 || d > 31) return false;
    tm value{};
    value.tm_year = y - 1900;
    value.tm_mon = m - 1;
    value.tm_mday = d;
    value.tm_hour = 12;
    mktime(&value);
    return value.tm_year == y - 1900 && value.tm_mon == m - 1 && value.tm_mday == d;
}

bool validTime(const string& timeText) {
    if (timeText.size() != 5 || timeText[2] != ':') return false;
    if (!isdigit(timeText[0]) || !isdigit(timeText[1]) || !isdigit(timeText[3]) || !isdigit(timeText[4])) return false;
    int hour = stoi(timeText.substr(0, 2));
    int minute = stoi(timeText.substr(3, 2));
    return hour >= 0 && hour <= 23 && minute >= 0 && minute <= 59;
}

string priorityName(int priority) {
    if (priority == 3) return "高";
    if (priority == 2) return "中";
    return "低";
}

vector<Recommendation> recommendations() {
    return {
        {"背诵英语单词 30 个", "英语", 2, 35, "适合每天碎片时间完成"},
        {"完成一道数据结构练习题", "数据结构", 3, 45, "建议先画图再写代码"},
        {"复习 C++ 文件读写", "C++", 2, 40, "重点理解 ifstream 和 ofstream"},
        {"整理今天的课堂笔记", "学习总结", 1, 25, "把知识点整理成提纲"},
        {"完成一页错题归纳", "复盘", 2, 30, "记录错误原因和正确思路"},
        {"阅读教材 10 页", "自主学习", 1, 30, "读完后写三句话总结"}
    };
}

void loadTasks() {
    tasks.clear();
    nextId = 1;
    ifstream in(DATA_FILE);
    string line;
    while (getline(in, line)) {
        vector<string> p = split(line, '|');
        if (p.size() != 12) continue;
        Task task;
        task.id = stoi(p[0]);
        task.title = p[1];
        task.topic = p[2];
        task.dueDate = p[3];
        task.dueTime = p[4];
        task.priority = stoi(p[5]);
        task.needReview = p[6] == "1";
        task.completed = p[7] == "1";
        task.createdDate = p[8];
        task.completedDate = p[9];
        task.estimatedMinutes = stoi(p[10]);
        task.note = p[11];
        tasks.push_back(task);
        nextId = max(nextId, task.id + 1);
    }
}

void saveTasks() {
    ofstream out(DATA_FILE);
    for (const Task& task : tasks) {
        out << task.id << '|'
            << cleanField(task.title) << '|'
            << cleanField(task.topic) << '|'
            << task.dueDate << '|'
            << task.dueTime << '|'
            << task.priority << '|'
            << (task.needReview ? 1 : 0) << '|'
            << (task.completed ? 1 : 0) << '|'
            << task.createdDate << '|'
            << task.completedDate << '|'
            << task.estimatedMinutes << '|'
            << cleanField(task.note) << '\n';
    }
}

Task* findTask(int id) {
    for (Task& task : tasks) {
        if (task.id == id) return &task;
    }
    return nullptr;
}

string taskJson(const Task& task) {
    stringstream ss;
    ss << "{"
       << "\"id\":" << task.id << ","
       << "\"title\":\"" << jsonEscape(task.title) << "\","
       << "\"topic\":\"" << jsonEscape(task.topic) << "\","
       << "\"dueDate\":\"" << task.dueDate << "\","
       << "\"dueTime\":\"" << task.dueTime << "\","
       << "\"priority\":" << task.priority << ","
       << "\"priorityName\":\"" << priorityName(task.priority) << "\","
       << "\"needReview\":" << (task.needReview ? "true" : "false") << ","
       << "\"completed\":" << (task.completed ? "true" : "false") << ","
       << "\"createdDate\":\"" << task.createdDate << "\","
       << "\"completedDate\":\"" << task.completedDate << "\","
       << "\"estimatedMinutes\":" << task.estimatedMinutes << ","
       << "\"note\":\"" << jsonEscape(task.note) << "\""
       << "}";
    return ss.str();
}

string allTasksJson() {
    stringstream ss;
    ss << "[";
    for (size_t i = 0; i < tasks.size(); ++i) {
        if (i > 0) ss << ",";
        ss << taskJson(tasks[i]);
    }
    ss << "]";
    return ss.str();
}

string recommendationsJson() {
    vector<Recommendation> list = recommendations();
    stringstream ss;
    ss << "[";
    for (size_t i = 0; i < list.size(); ++i) {
        if (i > 0) ss << ",";
        ss << "{"
           << "\"title\":\"" << jsonEscape(list[i].title) << "\","
           << "\"topic\":\"" << jsonEscape(list[i].topic) << "\","
           << "\"priority\":" << list[i].priority << ","
           << "\"estimatedMinutes\":" << list[i].estimatedMinutes << ","
           << "\"note\":\"" << jsonEscape(list[i].note) << "\""
           << "}";
    }
    ss << "]";
    return ss.str();
}

string remindersJson() {
    string today = todayDate();
    int todayDays = dateToDays(today);
    vector<string> items;
    for (const Task& task : tasks) {
        if (task.completed) continue;
        int diff = dateToDays(task.dueDate) - todayDays;
        string reason;
        if (diff < 0) reason = "已逾期";
        else if (diff == 0) reason = "今天截止";
        else if (task.priority == 3 && diff <= 7) reason = "高优先级，建议每天推进";
        else if (task.priority == 2 && diff <= 3) reason = "中优先级，截止时间较近";
        else if (task.priority == 1 && diff <= 1) reason = "低优先级，临近截止";
        if (!reason.empty()) items.push_back(task.title + "：" + reason);
    }
    for (const Task& task : tasks) {
        if (!task.completed || !task.needReview || task.completedDate == "-") continue;
        int passed = todayDays - dateToDays(task.completedDate);
        if (passed == 1 || passed == 3 || passed == 7) {
            items.push_back(task.title + " 已完成 " + to_string(passed) + " 天，建议复习");
        }
    }
    stringstream ss;
    ss << "[";
    for (size_t i = 0; i < items.size(); ++i) {
        if (i > 0) ss << ",";
        ss << "\"" << jsonEscape(items[i]) << "\"";
    }
    ss << "]";
    return ss.str();
}

string statsJson() {
    int total = static_cast<int>(tasks.size());
    int completed = 0;
    int minutes = 0;
    map<string, pair<int, int>> daily;
    map<string, pair<int, int>> topic;
    map<int, int> priorityCount;
    map<string, int> punchDays;

    for (const Task& task : tasks) {
        daily[task.createdDate].first++;
        topic[task.topic].first++;
        priorityCount[task.priority]++;
        minutes += task.estimatedMinutes;
        if (task.completed) {
            completed++;
            daily[task.createdDate].second++;
            topic[task.topic].second++;
            if (task.completedDate != "-") punchDays[task.completedDate]++;
        }
    }

    int rate = total == 0 ? 0 : completed * 100 / total;
    stringstream ss;
    ss << "{"
       << "\"total\":" << total << ","
       << "\"completed\":" << completed << ","
       << "\"todo\":" << total - completed << ","
       << "\"rate\":" << rate << ","
       << "\"estimatedMinutes\":" << minutes << ",";

    ss << "\"daily\":[";
    bool first = true;
    for (const auto& item : daily) {
        if (!first) ss << ",";
        first = false;
        int added = item.second.first;
        int done = item.second.second;
        int dayRate = added == 0 ? 0 : done * 100 / added;
        ss << "{\"date\":\"" << item.first << "\",\"added\":" << added << ",\"done\":" << done << ",\"rate\":" << dayRate << "}";
    }
    ss << "],";

    ss << "\"topic\":[";
    first = true;
    for (const auto& item : topic) {
        if (!first) ss << ",";
        first = false;
        int count = item.second.first;
        int done = item.second.second;
        int topicRate = count == 0 ? 0 : done * 100 / count;
        ss << "{\"topic\":\"" << jsonEscape(item.first) << "\",\"total\":" << count << ",\"done\":" << done << ",\"rate\":" << topicRate << "}";
    }
    ss << "],";

    ss << "\"priority\":[";
    for (int p = 3; p >= 1; --p) {
        if (p != 3) ss << ",";
        ss << "{\"priority\":" << p << ",\"name\":\"" << priorityName(p) << "\",\"count\":" << priorityCount[p] << "}";
    }
    ss << "],";

    ss << "\"punchDays\":[";
    first = true;
    for (const auto& item : punchDays) {
        if (!first) ss << ",";
        first = false;
        ss << "{\"date\":\"" << item.first << "\",\"count\":" << item.second << "}";
    }
    ss << "]}";
    return ss.str();
}

string validateTaskInput(const map<string, string>& data) {
    if (!data.count("title") || data.at("title").empty()) return "任务名称不能为空";
    if (!data.count("topic") || data.at("topic").empty()) return "学习主题不能为空";
    if (!data.count("dueDate") || !validDate(data.at("dueDate"))) return "完成日期格式错误";
    if (!data.count("dueTime") || !validTime(data.at("dueTime"))) return "完成时间格式错误";
    if (!data.count("priority")) return "优先级不能为空";
    int priority = stoi(data.at("priority"));
    if (priority < 1 || priority > 3) return "优先级只能是 1 到 3";
    return "";
}

string addTaskAction(const string& body) {
    map<string, string> data = parseForm(body);
    string error = validateTaskInput(data);
    if (!error.empty()) return "{\"ok\":false,\"message\":\"" + jsonEscape(error) + "\"}";

    Task task;
    task.id = nextId++;
    task.title = cleanField(data["title"]);
    task.topic = cleanField(data["topic"]);
    task.dueDate = data["dueDate"];
    task.dueTime = data["dueTime"];
    task.priority = stoi(data["priority"]);
    task.needReview = data.count("needReview") && data["needReview"] == "true";
    task.completed = false;
    task.createdDate = todayDate();
    task.completedDate = "-";
    task.estimatedMinutes = data.count("estimatedMinutes") && !data["estimatedMinutes"].empty() ? stoi(data["estimatedMinutes"]) : 30;
    task.note = data.count("note") ? cleanField(data["note"]) : "";
    tasks.push_back(task);
    saveTasks();
    return "{\"ok\":true,\"task\":" + taskJson(task) + "}";
}

string completeTaskAction(int id) {
    Task* task = findTask(id);
    if (!task) return "{\"ok\":false,\"message\":\"任务不存在\"}";
    task->completed = true;
    task->completedDate = todayDate();
    saveTasks();
    return "{\"ok\":true}";
}

string deleteTaskAction(int id) {
    size_t oldSize = tasks.size();
    tasks.erase(remove_if(tasks.begin(), tasks.end(), [id](const Task& task) {
        return task.id == id;
    }), tasks.end());
    if (tasks.size() == oldSize) return "{\"ok\":false,\"message\":\"任务不存在\"}";
    saveTasks();
    return "{\"ok\":true}";
}

string resetDemoData() {
    tasks.clear();
    nextId = 1;
    vector<Recommendation> seed = recommendations();
    for (size_t i = 0; i < 4; ++i) {
        Task task;
        task.id = nextId++;
        task.title = seed[i].title;
        task.topic = seed[i].topic;
        task.dueDate = todayDate();
        task.dueTime = i % 2 == 0 ? "20:00" : "21:30";
        task.priority = seed[i].priority;
        task.needReview = i % 2 == 0;
        task.completed = i == 0;
        task.createdDate = todayDate();
        task.completedDate = task.completed ? todayDate() : "-";
        task.estimatedMinutes = seed[i].estimatedMinutes;
        task.note = seed[i].note;
        tasks.push_back(task);
    }
    saveTasks();
    return "{\"ok\":true}";
}

string readFile(const string& path) {
    ifstream in(path, ios::binary);
    if (!in) return "";
    stringstream ss;
    ss << in.rdbuf();
    return ss.str();
}

string contentType(const string& path) {
    if (path.find(".css") != string::npos) return "text/css; charset=utf-8";
    if (path.find(".js") != string::npos) return "application/javascript; charset=utf-8";
    if (path.find(".html") != string::npos) return "text/html; charset=utf-8";
    return "text/plain; charset=utf-8";
}

void sendResponse(SOCKET client, const string& body, const string& type, int status = 200) {
    string statusText = status == 200 ? "OK" : (status == 404 ? "Not Found" : "Bad Request");
    stringstream response;
    response << "HTTP/1.1 " << status << " " << statusText << "\r\n"
             << "Content-Type: " << type << "\r\n"
             << "Access-Control-Allow-Origin: *\r\n"
             << "Access-Control-Allow-Methods: GET, POST, OPTIONS\r\n"
             << "Access-Control-Allow-Headers: Content-Type\r\n"
             << "Content-Length: " << body.size() << "\r\n"
             << "Connection: close\r\n\r\n"
             << body;
    string text = response.str();
    send(client, text.c_str(), static_cast<int>(text.size()), 0);
}

int idFromPath(const string& path, const string& suffix) {
    size_t start = string("/api/tasks/").size();
    size_t end = path.find(suffix);
    if (end == string::npos || end <= start) return -1;
    return stoi(path.substr(start, end - start));
}

void handleClient(SOCKET client) {
    char buffer[32768];
    int received = recv(client, buffer, sizeof(buffer) - 1, 0);
    if (received <= 0) return;
    buffer[received] = '\0';
    string request(buffer);

    string firstLine = request.substr(0, request.find("\r\n"));
    string method;
    string path;
    stringstream line(firstLine);
    line >> method >> path;

    size_t bodyPos = request.find("\r\n\r\n");
    string body = bodyPos == string::npos ? "" : request.substr(bodyPos + 4);

    try {
        if (method == "OPTIONS") sendResponse(client, "", "text/plain; charset=utf-8");
        else if (method == "GET" && path == "/api/tasks") sendResponse(client, allTasksJson(), "application/json; charset=utf-8");
        else if (method == "GET" && path == "/api/recommendations") sendResponse(client, recommendationsJson(), "application/json; charset=utf-8");
        else if (method == "GET" && path == "/api/reminders") sendResponse(client, remindersJson(), "application/json; charset=utf-8");
        else if (method == "GET" && path == "/api/stats") sendResponse(client, statsJson(), "application/json; charset=utf-8");
        else if (method == "POST" && path == "/api/tasks") sendResponse(client, addTaskAction(body), "application/json; charset=utf-8");
        else if (method == "POST" && path.find("/api/tasks/") == 0 && path.find("/complete") != string::npos) sendResponse(client, completeTaskAction(idFromPath(path, "/complete")), "application/json; charset=utf-8");
        else if (method == "POST" && path.find("/api/tasks/") == 0 && path.find("/delete") != string::npos) sendResponse(client, deleteTaskAction(idFromPath(path, "/delete")), "application/json; charset=utf-8");
        else if (method == "POST" && path == "/api/demo/reset") sendResponse(client, resetDemoData(), "application/json; charset=utf-8");
        else {
            string filePath = path == "/" ? "../frontend/index.html" : "../frontend" + path;
            string fileBody = readFile(filePath);
            if (fileBody.empty()) sendResponse(client, "404 Not Found", "text/plain; charset=utf-8", 404);
            else sendResponse(client, fileBody, contentType(filePath));
        }
    } catch (...) {
        sendResponse(client, "{\"ok\":false,\"message\":\"后端处理请求失败\"}", "application/json; charset=utf-8", 400);
    }
}

int main() {
    loadTasks();
    WSADATA wsaData;
    if (WSAStartup(MAKEWORD(2, 2), &wsaData) != 0) {
        cout << "网络库启动失败\n";
        return 1;
    }

    SOCKET serverSocket = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
    sockaddr_in addr{};
    addr.sin_family = AF_INET;
    addr.sin_addr.s_addr = INADDR_ANY;
    addr.sin_port = htons(PORT);

    if (bind(serverSocket, reinterpret_cast<sockaddr*>(&addr), sizeof(addr)) == SOCKET_ERROR) {
        cout << "端口 " << PORT << " 被占用，请关闭其他程序后再运行。\n";
        closesocket(serverSocket);
        WSACleanup();
        return 1;
    }

    listen(serverSocket, SOMAXCONN);
    cout << "学习养成计划 V2 后端已启动：http://localhost:" << PORT << "\n";
    cout << "浏览器打开上面的地址即可使用。按 Ctrl+C 停止服务。\n";

    while (true) {
        SOCKET client = accept(serverSocket, nullptr, nullptr);
        if (client != INVALID_SOCKET) {
            handleClient(client);
            closesocket(client);
        }
    }

    closesocket(serverSocket);
    WSACleanup();
    return 0;
}
