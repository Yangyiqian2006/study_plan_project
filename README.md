# 学习养成计划 V2（前端 + C++ 后端）

本版本是独立重写版本，不修改原来的 `web`、`fullstack`、`software` 文件夹。

## 项目定位

本项目最终呈现为一个前端 + 后端结构的学习养成计划软件。

- 前端负责页面展示、用户交互和可视化。
- 后端负责数据保存、任务管理、提醒规则和统计分析。
- 数据保存在后端生成的 `study_tasks_v2.txt` 文件中。

## 技术栈

1. C++：编写后端 HTTP 服务，处理任务数据和业务逻辑。
2. HTML：编写网页结构。
3. CSS：编写页面样式和响应式布局。
4. JavaScript：编写前端交互逻辑，调用后端接口并渲染页面。
5. WinSock：C++ 后端使用 Windows 网络接口实现本地 HTTP 服务。
6. 文本文件存储：使用 `.txt` 文件保存任务数据。

## 使用的数据结构

### C++ 后端

1. `struct Task`

用于表示一个学习任务，包含任务编号、名称、主题、截止时间、优先级、复习提醒、完成状态、创建日期、完成日期、预计时长和备注。

2. `struct Recommendation`

用于表示系统推荐任务。

3. `vector<Task>`

用于保存所有任务，支持遍历、添加、删除和统计。

4. `vector<Recommendation>`

用于保存系统推荐任务。

5. `map<string, pair<int, int>>`

用于按日期和主题统计任务数量、完成数量和完成率。

6. `map<int, int>`

用于统计不同优先级任务数量。

7. `map<string, int>`

用于统计每天的打卡次数，生成打卡日历。

### JavaScript 前端

1. `Array`

用于保存从后端获取的任务列表、推荐任务列表、每日统计和主题统计。

2. `Object`

用于表示任务、统计数据、接口地址等结构化数据。

3. `Map`

用于前端生成打卡日历时按日期快速查找打卡次数。

4. DOM 节点集合

用于批量处理导航按钮、筛选按钮和页面视图切换。

## 项目结构

```text
fullstack_v2/
  backend/
    server.cpp
    server.exe
    study_tasks_v2.txt
  frontend/
    index.html
    styles.css
    app.js
  docs/
    TEST_CASES.md
    TEST_REPORT.md
    DEFECT_TRACKING.md
  README.md
```

## 运行方式

进入 `backend` 文件夹，运行：

```powershell
.\server.exe
```

然后浏览器打开：

```text
http://localhost:8090
```

如果需要重新编译后端：

```powershell
g++ server.cpp -std=c++17 -lws2_32 -o server.exe
```

## 功能说明

1. 添加学习任务：输入任务名称、主题、截止日期、截止时间、优先级、预计时长、备注和是否复习提醒。
2. 系统推荐任务：由后端提供推荐任务，前端点击后自动填入表单。
3. 任务管理：支持查看、筛选、打卡和删除任务。
4. 提醒功能：后端根据任务截止时间、优先级和复习规则生成提醒。
5. 打卡记录：任务完成后保存完成日期，并在打卡表和日历中展示。
6. 数据分析：统计总任务数、完成数、完成率、预计学习时长、每日完成率和主题完成率。
7. 可视化展示：使用指标卡、进度条、日历、统计卡片展示学习情况。

## 前端和后端的关系

前端不直接保存任务数据。用户在网页上点击按钮后，JavaScript 会通过 HTTP 请求访问 C++ 后端接口。后端处理数据后返回 JSON，前端再根据返回结果更新页面。

例如：

- 前端添加任务：`POST /api/tasks`
- 后端保存任务：写入 `study_tasks_v2.txt`
- 前端刷新任务列表：`GET /api/tasks`
- 后端返回 JSON：任务数组

## 接口列表

- `GET /api/tasks`：获取任务列表。
- `GET /api/recommendations`：获取系统推荐任务。
- `GET /api/reminders`：获取提醒信息。
- `GET /api/stats`：获取统计分析数据。
- `POST /api/tasks`：添加任务。
- `POST /api/tasks/{id}/complete`：完成任务并打卡。
- `POST /api/tasks/{id}/delete`：删除任务。
- `POST /api/demo/reset`：生成演示数据。
