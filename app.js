const API = {
  tasks: "/api/tasks",
  stats: "/api/stats",
  reminders: "/api/reminders",
  recommendations: "/api/recommendations",
  resetDemo: "/api/demo/reset"
};

let tasks = [];
let stats = { total: 0, completed: 0, todo: 0, rate: 0, estimatedMinutes: 0, daily: [], topic: [], priority: [], punchDays: [] };
let recommendations = [];
let currentFilter = "all";

const $ = selector => document.querySelector(selector);
const $$ = selector => Array.from(document.querySelectorAll(selector));

const el = {
  todayLabel: $("#todayLabel"),
  pageTitle: $("#pageTitle"),
  reminderList: $("#reminderList"),
  serverState: $("#serverState"),
  totalCount: $("#totalCount"),
  doneCount: $("#doneCount"),
  rateCount: $("#rateCount"),
  minuteCount: $("#minuteCount"),
  progressHint: $("#progressHint"),
  mainProgress: $("#mainProgress"),
  priorityBars: $("#priorityBars"),
  recommendList: $("#recommendList"),
  taskForm: $("#taskForm"),
  titleInput: $("#titleInput"),
  topicInput: $("#topicInput"),
  dateInput: $("#dateInput"),
  timeInput: $("#timeInput"),
  priorityInput: $("#priorityInput"),
  minuteInput: $("#minuteInput"),
  noteInput: $("#noteInput"),
  reviewInput: $("#reviewInput"),
  taskList: $("#taskList"),
  monthInput: $("#monthInput"),
  calendar: $("#calendar"),
  recordTable: $("#recordTable"),
  dailyStats: $("#dailyStats"),
  topicStats: $("#topicStats"),
  refreshBtn: $("#refreshBtn"),
  resetDemoBtn: $("#resetDemoBtn"),
  toast: $("#toast")
};

function today() {
  return new Date().toISOString().slice(0, 10);
}

function monthNow() {
  return new Date().toISOString().slice(0, 7);
}

function priorityClass(priority) {
  if (priority === 3) return "high";
  if (priority === 2) return "middle";
  return "low";
}

function priorityName(priority) {
  if (priority === 3) return "高";
  if (priority === 2) return "中";
  return "低";
}

function showToast(message) {
  el.toast.textContent = message;
  el.toast.classList.add("show");
  setTimeout(() => el.toast.classList.remove("show"), 1800);
}

async function getJson(url) {
  const response = await fetch(url);
  if (!response.ok) throw new Error("后端请求失败");
  return response.json();
}

async function postForm(url, data = {}) {
  const params = new URLSearchParams();
  Object.entries(data).forEach(([key, value]) => params.append(key, value));
  const response = await fetch(url, {
    method: "POST",
    headers: { "Content-Type": "application/x-www-form-urlencoded" },
    body: params.toString()
  });
  if (!response.ok) throw new Error("后端提交失败");
  return response.json();
}

function setServerState(ok, message) {
  el.serverState.textContent = message;
  el.serverState.classList.toggle("ok", ok);
  el.serverState.classList.toggle("bad", !ok);
}

async function loadAll() {
  try {
    const [taskData, statData, reminderData, recommendationData] = await Promise.all([
      getJson(API.tasks),
      getJson(API.stats),
      getJson(API.reminders),
      getJson(API.recommendations)
    ]);
    tasks = taskData;
    stats = statData;
    recommendations = recommendationData;
    setServerState(true, "已连接 C++ 后端服务");
    renderAll(reminderData);
  } catch (error) {
    setServerState(false, "无法连接后端，请先运行 backend/server.exe");
    el.taskList.innerHTML = `<article class="task-card">请先启动 C++ 后端，再打开 http://localhost:8090。</article>`;
  }
}

async function addTaskFromForm(event) {
  event.preventDefault();
  const result = await postForm(API.tasks, {
    title: el.titleInput.value.trim(),
    topic: el.topicInput.value.trim(),
    dueDate: el.dateInput.value,
    dueTime: el.timeInput.value,
    priority: el.priorityInput.value,
    estimatedMinutes: el.minuteInput.value,
    note: el.noteInput.value.trim(),
    needReview: el.reviewInput.checked ? "true" : "false"
  });
  if (!result.ok) {
    showToast(result.message || "添加失败");
    return;
  }
  el.taskForm.reset();
  setDefaultInputs();
  showToast("任务已提交给 C++ 后端");
  await loadAll();
}

async function completeTask(id) {
  const result = await postForm(`/api/tasks/${id}/complete`);
  if (result.ok) showToast("打卡成功");
  await loadAll();
}

async function deleteTask(id) {
  if (!confirm("确定删除这个任务吗？")) return;
  const result = await postForm(`/api/tasks/${id}/delete`);
  if (result.ok) showToast("任务已删除");
  await loadAll();
}

async function resetDemoData() {
  if (!confirm("会用演示数据覆盖当前后端任务，确定继续吗？")) return;
  await postForm(API.resetDemo);
  showToast("演示数据已生成");
  await loadAll();
}

function renderAll(reminders) {
  renderMetrics();
  renderReminders(reminders);
  renderRecommendations();
  renderTasks();
  renderRecords();
  renderCalendar();
  renderAnalysis();
}

function renderMetrics() {
  el.totalCount.textContent = stats.total;
  el.doneCount.textContent = stats.completed;
  el.rateCount.textContent = `${stats.rate}%`;
  el.minuteCount.textContent = stats.estimatedMinutes;
  el.mainProgress.style.width = `${stats.rate}%`;
  el.progressHint.textContent = `已完成 ${stats.completed}/${stats.total}`;
  renderPriorityBars();
}

function renderPriorityBars() {
  const max = Math.max(1, ...stats.priority.map(item => item.count));
  el.priorityBars.innerHTML = stats.priority.map(item => {
    const width = Math.round(item.count * 100 / max);
    return `
      <div class="mini-row">
        <strong>${item.name}优先级</strong>
        <div class="mini-track"><div class="mini-fill" style="width:${width}%"></div></div>
        <span>${item.count}</span>
      </div>
    `;
  }).join("");
}

function renderReminders(reminders) {
  el.reminderList.innerHTML = reminders.length
    ? reminders.map(text => `<div class="reminder">${text}</div>`).join("")
    : `<div class="reminder">今天没有需要提醒的任务。</div>`;
}

function renderRecommendations() {
  el.recommendList.innerHTML = recommendations.map((item, index) => `
    <article class="recommend-card">
      <div>
        <strong>${item.title}</strong>
        <div class="meta">
          <span class="badge">${item.topic}</span>
          <span class="badge ${priorityClass(item.priority)}">${priorityName(item.priority)}优先级</span>
          <span class="badge">${item.estimatedMinutes} 分钟</span>
        </div>
        <p class="task-note">${item.note}</p>
      </div>
      <button class="small-btn" data-recommend="${index}">采用</button>
    </article>
  `).join("");
}

function filteredTasks() {
  if (currentFilter === "todo") return tasks.filter(task => !task.completed);
  if (currentFilter === "done") return tasks.filter(task => task.completed);
  if (currentFilter === "high") return tasks.filter(task => task.priority === 3);
  return tasks;
}

function renderTasks() {
  const visible = filteredTasks();
  if (visible.length === 0) {
    el.taskList.innerHTML = `<article class="task-card">当前筛选条件下暂无任务。</article>`;
    return;
  }
  el.taskList.innerHTML = visible.map(task => `
    <article class="task-card ${task.completed ? "done" : ""}">
      <div>
        <div class="task-title">${task.title}</div>
        <div class="meta">
          <span class="badge">${task.topic}</span>
          <span class="badge ${priorityClass(task.priority)}">${priorityName(task.priority)}优先级</span>
          <span class="badge">截止 ${task.dueDate} ${task.dueTime}</span>
          <span class="badge">${task.estimatedMinutes} 分钟</span>
          <span class="badge">${task.needReview ? "需要复习" : "无需复习"}</span>
          <span class="badge">${task.completed ? `已完成 ${task.completedDate}` : "未完成"}</span>
        </div>
        ${task.note ? `<p class="task-note">${task.note}</p>` : ""}
      </div>
      <div class="actions">
        <button class="small-btn done" data-complete="${task.id}" ${task.completed ? "disabled" : ""}>打卡</button>
        <button class="small-btn delete" data-delete="${task.id}">删除</button>
      </div>
    </article>
  `).join("");
}

function renderRecords() {
  const doneTasks = tasks.filter(task => task.completed).sort((a, b) => b.completedDate.localeCompare(a.completedDate));
  el.recordTable.innerHTML = doneTasks.length
    ? doneTasks.map(task => `<tr><td>${task.completedDate}</td><td>${task.title}</td><td>${task.topic}</td><td>${task.estimatedMinutes} 分钟</td></tr>`).join("")
    : `<tr><td colspan="4">暂无打卡记录</td></tr>`;
}

function renderCalendar() {
  const value = el.monthInput.value || monthNow();
  const [year, month] = value.split("-").map(Number);
  const firstDay = new Date(year, month - 1, 1).getDay();
  const totalDays = new Date(year, month, 0).getDate();
  const hit = new Map();
  stats.punchDays.forEach(item => {
    if (item.date.startsWith(value)) hit.set(Number(item.date.slice(8, 10)), item.count);
  });
  const cells = ["日", "一", "二", "三", "四", "五", "六"].map(name => `<div class="day-name">${name}</div>`);
  for (let i = 0; i < firstDay; i++) cells.push(`<div class="day-cell empty"></div>`);
  for (let day = 1; day <= totalDays; day++) {
    const count = hit.get(day) || 0;
    cells.push(`<div class="day-cell ${count ? "hit" : ""}">${day}${count ? `<small>${count}</small>` : ""}</div>`);
  }
  el.calendar.innerHTML = cells.join("");
}

function renderAnalysis() {
  el.dailyStats.innerHTML = stats.daily.length
    ? stats.daily.map(item => `
      <article class="stat-card">
        <span>${item.date}</span>
        <strong>${item.rate}%</strong>
        <div class="day-track"><div class="day-fill" style="width:${item.rate}%"></div></div>
        <p class="subtle">添加 ${item.added} 个，完成 ${item.done} 个</p>
      </article>
    `).join("")
    : `<article class="stat-card">暂无每日统计数据。</article>`;

  el.topicStats.innerHTML = stats.topic.length
    ? stats.topic.map(item => `
      <article class="topic-card">
        <strong>${item.topic}</strong>
        <div class="topic-track"><div class="topic-fill" style="width:${item.rate}%"></div></div>
        <span>${item.rate}%</span>
      </article>
    `).join("")
    : `<article class="topic-card">暂无主题统计数据。</article>`;
}

function useRecommendation(index) {
  const item = recommendations[index];
  if (!item) return;
  el.titleInput.value = item.title;
  el.topicInput.value = item.topic;
  el.priorityInput.value = String(item.priority);
  el.minuteInput.value = item.estimatedMinutes;
  el.noteInput.value = item.note;
  el.reviewInput.checked = item.priority >= 2;
  switchView("tasks");
}

function switchView(viewName) {
  $$(".nav-item").forEach(item => item.classList.toggle("active", item.dataset.view === viewName));
  $$(".view").forEach(view => view.classList.remove("active"));
  $(`#${viewName}View`).classList.add("active");
  const titleMap = { dashboard: "学习总览", tasks: "任务管理", records: "打卡记录", analysis: "数据分析" };
  el.pageTitle.textContent = titleMap[viewName];
}

function setDefaultInputs() {
  el.dateInput.value = today();
  el.timeInput.value = "20:00";
  el.priorityInput.value = "2";
  el.minuteInput.value = "30";
}

function bindEvents() {
  el.taskForm.addEventListener("submit", addTaskFromForm);
  el.refreshBtn.addEventListener("click", () => loadAll().then(() => showToast("数据已刷新")));
  el.resetDemoBtn.addEventListener("click", resetDemoData);
  el.monthInput.addEventListener("change", renderCalendar);

  el.recommendList.addEventListener("click", event => {
    const button = event.target.closest("[data-recommend]");
    if (button) useRecommendation(Number(button.dataset.recommend));
  });

  el.taskList.addEventListener("click", event => {
    const completeButton = event.target.closest("[data-complete]");
    const deleteButton = event.target.closest("[data-delete]");
    if (completeButton) completeTask(Number(completeButton.dataset.complete));
    if (deleteButton) deleteTask(Number(deleteButton.dataset.delete));
  });

  $$(".filter").forEach(button => {
    button.addEventListener("click", () => {
      currentFilter = button.dataset.filter;
      $$(".filter").forEach(item => item.classList.remove("active"));
      button.classList.add("active");
      renderTasks();
    });
  });

  $$(".nav-item").forEach(button => {
    button.addEventListener("click", () => switchView(button.dataset.view));
  });
}

el.todayLabel.textContent = `今天是 ${today()}`;
el.monthInput.value = monthNow();
setDefaultInputs();
bindEvents();
loadAll();
