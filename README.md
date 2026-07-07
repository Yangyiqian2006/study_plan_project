# 学习养成计划 V3（注册登录版）

本版本是在 V2 前端 + C++ 后端基础上重新设计的 V3，新增用户注册、登录和按用户隔离任务功能。

## 技术栈

- 后端：C++、WinSock、本地文本文件存储
- 前端：HTML、CSS、JavaScript
- 通信方式：HTTP 接口 + JSON
- 运行环境：Windows + 浏览器

## 新增功能

1. 用户注册：用户输入用户名、显示名称和密码。
2. 用户登录：用户输入用户名和密码后进入系统。
3. 退出登录：清除浏览器保存的当前登录用户。
4. 用户数据隔离：A 用户看不到 B 用户的任务。
5. 用户文件保存：用户保存到 `users_v3.txt`。
6. 任务文件保存：任务保存到 `study_tasks_v3.txt`，任务中增加 username 字段。

## 项目结构

```text
fullstack_v3/
  backend/
    server.cpp
    server.exe
    users_v3.txt
    study_tasks_v3.txt
  frontend/
    index.html
    styles.css
    app.js
  docs/
  .vscode/
  compile_backend.bat
  run_backend.bat
```

## 运行方式

最简单方式：双击 `run_backend.bat`。

或命令行运行：

```powershell
cd "D:\Yiqian_Yang _Homework_c++\project\fullstack_v3\backend"
.\server.exe
```

浏览器打开：

```text
http://localhost:8090
```

## 编译方式

```powershell
g++ server.cpp -std=c++17 -finput-charset=UTF-8 -fexec-charset=UTF-8 -static -static-libgcc -static-libstdc++ -o server.exe -lws2_32
```

## 主要接口

| 接口 | 方法 | 作用 |
|---|---|---|
| /api/register | POST | 注册用户 |
| /api/login | POST | 登录用户 |
| /api/tasks?username=xxx | GET | 获取当前用户任务 |
| /api/tasks | POST | 添加当前用户任务 |
| /api/tasks/{id}/complete?username=xxx | POST | 完成当前用户任务 |
| /api/tasks/{id}/delete?username=xxx | POST | 删除当前用户任务 |
| /api/stats?username=xxx | GET | 获取当前用户统计 |
| /api/reminders?username=xxx | GET | 获取当前用户提醒 |
| /api/recommendations | GET | 获取系统推荐任务 |
| /api/demo/reset?username=xxx | POST | 生成当前用户演示数据 |

## 使用的数据结构

### C++ 后端

- `struct User`：保存用户账号、密码、显示名称、注册日期。
- `struct Task`：保存任务数据，新增 `username` 字段用于区分用户。
- `struct Recommendation`：保存系统推荐任务。
- `vector<User>`：保存全部用户。
- `vector<Task>`：保存全部任务。
- `map<string, pair<int,int>>`：按日期和主题统计。
- `map<int,int>`：按优先级统计。
- `map<string,int>`：按打卡日期统计。

### JavaScript 前端

- `Object`：保存接口地址、当前用户、统计对象。
- `Array`：保存任务列表、推荐任务、统计列表。
- `Map`：生成打卡日历时按日期快速查找。
- DOM 节点集合：控制页面显示和事件绑定。

## 说明

本项目是课程作业级前后端项目，不使用数据库和加密库。密码以文本形式保存，方便学习理解，不适合作为真实系统直接使用。
