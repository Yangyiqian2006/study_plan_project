# CSS ???? styles.css ????

????`D:\Yiqian_Yang _Homework_c++\project\fullstack_v2\frontend\styles.css`

???????????????????????????

| ?? | ?? | ?? |
|---:|---|---|
| 1 | `<code>:root {</code>` | ???? CSS ??????????? |
| 2 | `<code>  --bg: #eef2f8;</code>` | CSS ????? |
| 3 | `<code>  --surface: #ffffff;</code>` | CSS ????? |
| 4 | `<code>  --surface-soft: #f8fafc;</code>` | CSS ????? |
| 5 | `<code>  --ink: #172033;</code>` | CSS ????? |
| 6 | `<code>  --muted: #667085;</code>` | CSS ????? |
| 7 | `<code>  --line: #d7deea;</code>` | CSS ????? |
| 8 | `<code>  --blue: #2864e8;</code>` | CSS ????? |
| 9 | `<code>  --green: #159a63;</code>` | CSS ????? |
| 10 | `<code>  --orange: #c77719;</code>` | CSS ????? |
| 11 | `<code>  --purple: #7c4dff;</code>` | CSS ????? |
| 12 | `<code>  --red: #d64545;</code>` | CSS ????? |
| 13 | `<code>  --shadow: 0 18px 42px rgba(23, 32, 51, 0.09);</code>` | CSS ????? |
| 14 | `<code>}</code>` | ?????? |
| 15 | `<code>* { box-sizing: border-box; }</code>` | ???????? |
| 16 | `<code>body { margin: 0; min-height: 100vh; color: var(--ink); background: var(--bg); font-family: &quot;Microsoft YaHei&quot;, Arial, sans-serif; }</code>` | CSS ????? |
| 17 | `<code>button, input, select, textarea { font: inherit; }</code>` | ??????????? |
| 18 | `<code>button { cursor: pointer; }</code>` | ?? CSS ???????????? |
| 19 | `<code>.app { min-height: 100vh; display: grid; grid-template-columns: 304px 1fr; }</code>` | ????????? grid ? flex? |
| 20 | `<code>.sidebar { background: var(--surface); border-right: 1px solid var(--line); padding: 24px; display: flex; flex-direction: column; gap: 22px; }</code>` | CSS ????? |
| 21 | `<code>.brand { display: flex; align-items: center; gap: 12px; }</code>` | ????????? grid ? flex? |
| 22 | `<code>.logo { width: 48px; height: 48px; border-radius: 8px; background: var(--blue); color: #fff; display: grid; place-items: center; font-size: 23px; font-weight: 900; }</code>` | CSS ????? |
| 23 | `<code>h1, h2, h3, p { margin: 0; }</code>` | ?????????? |
| 24 | `<code>h1 { font-size: 20px; }</code>` | ??????????? |
| 25 | `<code>.brand p, .subtle { color: var(--muted); font-size: 14px; }</code>` | CSS ????? |
| 26 | `<code>.nav { display: grid; gap: 8px; }</code>` | ????????? grid ? flex? |
| 27 | `<code>.nav-item { border: 0; background: transparent; color: var(--muted); border-radius: 8px; padding: 12px 14px; text-align: left; }</code>` | CSS ????? |
| 28 | `<code>.nav-item:hover, .nav-item.active { background: #eef4ff; color: var(--blue); font-weight: 800; }</code>` | CSS ????? |
| 29 | `<code>.side-card, .panel, .metric-card { background: var(--surface); border: 1px solid var(--line); border-radius: 8px; box-shadow: var(--shadow); }</code>` | CSS ????? |
| 30 | `<code>.side-card { padding: 16px; }</code>` | ?????????? |
| 31 | `<code>.side-card.compact { box-shadow: none; }</code>` | ??????? |
| 32 | `<code>.side-title { font-weight: 800; margin-bottom: 10px; }</code>` | ?????????? |
| 33 | `<code>.reminder-list { display: grid; gap: 9px; }</code>` | ????????? grid ? flex? |
| 34 | `<code>.reminder { border-left: 4px solid var(--blue); background: var(--surface-soft); border-radius: 8px; padding: 10px; font-size: 14px; line-height: 1.45; }</code>` | CSS ????? |
| 35 | `<code>.server-state { color: var(--muted); line-height: 1.5; }</code>` | CSS ????? |
| 36 | `<code>.server-state.ok { color: var(--green); font-weight: 700; }</code>` | CSS ????? |
| 37 | `<code>.server-state.bad { color: var(--red); font-weight: 700; }</code>` | CSS ????? |
| 38 | `<code>.main { padding: 26px; overflow: auto; }</code>` | ?????????? |
| 39 | `<code>.hero { display: flex; align-items: center; justify-content: space-between; gap: 16px; margin-bottom: 18px; }</code>` | ????????? grid ? flex? |
| 40 | `<code>.hero h2 { font-size: 28px; margin-top: 6px; }</code>` | ?????????? |
| 41 | `<code>.hero-actions { display: flex; gap: 10px; flex-wrap: wrap; }</code>` | ????????? grid ? flex? |
| 42 | `<code>.primary-btn, .ghost-btn, .small-btn, .filter { border: 0; border-radius: 8px; font-weight: 800; }</code>` | ???????? |
| 43 | `<code>.primary-btn { background: var(--blue); color: #fff; padding: 12px 15px; }</code>` | CSS ????? |
| 44 | `<code>.ghost-btn, .small-btn, .filter { background: #edf2f7; color: var(--ink); padding: 10px 12px; }</code>` | CSS ????? |
| 45 | `<code>.small-btn.done { background: #e8f7ef; color: var(--green); }</code>` | CSS ????? |
| 46 | `<code>.small-btn.delete { background: #fff0f0; color: var(--red); }</code>` | CSS ????? |
| 47 | `<code>.metric-grid { display: grid; grid-template-columns: repeat(4, minmax(150px, 1fr)); gap: 14px; margin-bottom: 18px; }</code>` | ????????? grid ? flex? |
| 48 | `<code>.metric-card { padding: 18px; position: relative; overflow: hidden; }</code>` | ?????????? |
| 49 | `<code>.metric-card span { color: var(--muted); font-size: 14px; }</code>` | CSS ????? |
| 50 | `<code>.metric-card strong { display: block; font-size: 32px; margin: 8px 0 4px; }</code>` | ????????? grid ? flex? |
| 51 | `<code>.metric-card small { color: var(--muted); }</code>` | CSS ????? |
| 52 | `<code>.metric-card::after { content: &quot;&quot;; position: absolute; right: 16px; top: 18px; width: 34px; height: 34px; border-radius: 8px; opacity: .18; }</code>` | ???????? |
| 53 | `<code>.accent-blue::after { background: var(--blue); }</code>` | CSS ????? |
| 54 | `<code>.accent-green::after { background: var(--green); }</code>` | CSS ????? |
| 55 | `<code>.accent-orange::after { background: var(--orange); }</code>` | CSS ????? |
| 56 | `<code>.accent-purple::after { background: var(--purple); }</code>` | CSS ????? |
| 57 | `<code>.view { display: none; }</code>` | ????????? grid ? flex? |
| 58 | `<code>.view.active { display: block; }</code>` | ????????? grid ? flex? |
| 59 | `<code>.dashboard-grid, .editor-grid, .records-grid, .analysis-grid { display: grid; gap: 18px; }</code>` | ????????? grid ? flex? |
| 60 | `<code>.dashboard-grid { grid-template-columns: minmax(360px, 1.2fr) minmax(320px, .8fr); }</code>` | ????????? |
| 61 | `<code>.editor-grid { grid-template-columns: minmax(340px, 430px) 1fr; }</code>` | ????????? |
| 62 | `<code>.records-grid, .analysis-grid { grid-template-columns: 1fr 1fr; }</code>` | ????????? |
| 63 | `<code>.panel { padding: 18px; }</code>` | ?????????? |
| 64 | `<code>.large-panel { min-height: 280px; }</code>` | ???????? |
| 65 | `<code>.panel-head { display: flex; align-items: center; justify-content: space-between; gap: 12px; margin-bottom: 14px; }</code>` | ????????? grid ? flex? |
| 66 | `<code>.big-progress { height: 28px; border-radius: 999px; background: #e6ebf3; overflow: hidden; margin: 20px 0; }</code>` | ???????? |
| 67 | `<code>.big-progress div { height: 100%; width: 0; background: var(--green); transition: width .25s ease; }</code>` | CSS ????? |
| 68 | `<code>.mini-bars, .recommend-list, .task-list, .stat-list, .topic-list { display: grid; gap: 12px; }</code>` | ????????? grid ? flex? |
| 69 | `<code>.mini-row, .recommend-card, .task-card, .stat-card, .topic-card { border: 1px solid var(--line); border-radius: 8px; background: #fff; padding: 14px; }</code>` | CSS ????? |
| 70 | `<code>.mini-row { display: grid; grid-template-columns: 90px 1fr 42px; align-items: center; gap: 10px; }</code>` | ????????? grid ? flex? |
| 71 | `<code>.mini-track, .topic-track, .day-track { height: 10px; background: #e8edf5; border-radius: 999px; overflow: hidden; }</code>` | ???????? |
| 72 | `<code>.mini-fill, .topic-fill, .day-fill { height: 100%; background: var(--blue); }</code>` | CSS ????? |
| 73 | `<code>.recommend-card { display: grid; grid-template-columns: 1fr auto; gap: 12px; align-items: center; }</code>` | ????????? grid ? flex? |
| 74 | `<code>.meta { display: flex; flex-wrap: wrap; gap: 8px; margin-top: 9px; }</code>` | ????????? grid ? flex? |
| 75 | `<code>.badge { display: inline-flex; min-height: 26px; align-items: center; border-radius: 999px; padding: 4px 8px; background: #edf2f7; color: #475467; font-size: 13px; }</code>` | ????????? grid ? flex? |
| 76 | `<code>.badge.high { background: #fff0f0; color: var(--red); }</code>` | CSS ????? |
| 77 | `<code>.badge.middle { background: #fff7e6; color: var(--orange); }</code>` | CSS ????? |
| 78 | `<code>.badge.low { background: #e8f7ef; color: var(--green); }</code>` | CSS ????? |
| 79 | `<code>form { display: grid; gap: 13px; }</code>` | ????????? grid ? flex? |
| 80 | `<code>label { display: grid; gap: 7px; color: #344054; font-size: 14px; }</code>` | ????????? grid ? flex? |
| 81 | `<code>input, select, textarea { border: 1px solid var(--line); border-radius: 8px; padding: 11px 12px; background: #fff; color: var(--ink); width: 100%; }</code>` | CSS ????? |
| 82 | `<code>textarea { resize: vertical; }</code>` | ?? CSS ???????????? |
| 83 | `<code>.two-col { display: grid; grid-template-columns: 1fr 1fr; gap: 12px; }</code>` | ????????? grid ? flex? |
| 84 | `<code>.check-row { display: flex; align-items: center; gap: 9px; }</code>` | ????????? grid ? flex? |
| 85 | `<code>.check-row input { width: 18px; height: 18px; }</code>` | ???????? |
| 86 | `<code>.filter-row { display: flex; gap: 9px; flex-wrap: wrap; margin-bottom: 14px; }</code>` | ????????? grid ? flex? |
| 87 | `<code>.filter.active { background: var(--blue); color: #fff; }</code>` | CSS ????? |
| 88 | `<code>.task-card { display: grid; grid-template-columns: 1fr auto; gap: 12px; align-items: center; }</code>` | ????????? grid ? flex? |
| 89 | `<code>.task-card.done { opacity: .7; }</code>` | ??????????? |
| 90 | `<code>.task-title { font-weight: 900; font-size: 17px; }</code>` | ??????????? |
| 91 | `<code>.task-note { color: var(--muted); margin-top: 8px; line-height: 1.5; }</code>` | CSS ????? |
| 92 | `<code>.actions { display: flex; gap: 8px; }</code>` | ????????? grid ? flex? |
| 93 | `<code>.calendar { display: grid; grid-template-columns: repeat(7, 1fr); gap: 8px; }</code>` | ????????? grid ? flex? |
| 94 | `<code>.day-name, .day-cell { min-height: 48px; display: grid; place-items: center; border-radius: 8px; }</code>` | ????????? grid ? flex? |
| 95 | `<code>.day-name { color: var(--muted); font-weight: 800; }</code>` | CSS ????? |
| 96 | `<code>.day-cell { background: var(--surface-soft); border: 1px solid var(--line); }</code>` | CSS ????? |
| 97 | `<code>.day-cell.hit { background: #e8f7ef; color: var(--green); font-weight: 900; }</code>` | CSS ????? |
| 98 | `<code>.day-cell.empty { visibility: hidden; }</code>` | ?? CSS ???????????? |
| 99 | `<code>.table-wrap { overflow-x: auto; }</code>` | ?? CSS ???????????? |
| 100 | `<code>table { width: 100%; border-collapse: collapse; }</code>` | ???????? |
| 101 | `<code>th, td { padding: 12px; border-bottom: 1px solid var(--line); text-align: left; }</code>` | CSS ????? |
| 102 | `<code>th { background: var(--surface-soft); }</code>` | CSS ????? |
| 103 | `<code>.stat-card { display: grid; gap: 8px; }</code>` | ????????? grid ? flex? |
| 104 | `<code>.stat-card strong { font-size: 24px; }</code>` | ??????????? |
| 105 | `<code>.topic-card { display: grid; grid-template-columns: 150px 1fr 60px; gap: 12px; align-items: center; }</code>` | ????????? grid ? flex? |
| 106 | `<code>.toast { position: fixed; right: 24px; bottom: 24px; max-width: 320px; background: #172033; color: #fff; padding: 13px 15px; border-radius: 8px; box-shadow: var(--shadow); transform: translateY(90px); opacity: 0; transition: .22s ease; }</code>` | CSS ????? |
| 107 | `<code>.toast.show { transform: translateY(0); opacity: 1; }</code>` | ??????????? |
| 108 | `<code>@media (max-width: 1080px) { .app { grid-template-columns: 1fr; } .sidebar { border-right: 0; border-bottom: 1px solid var(--line); } .dashboard-grid, .editor-grid, .records-grid, .analysis-grid { grid-template-columns: 1fr; } }</code>` | ????????????????? |
| 109 | `<code>@media (max-width: 720px) { .main, .sidebar { padding: 16px; } .hero { align-items: flex-start; flex-direction: column; } .metric-grid { grid-template-columns: repeat(2, 1fr); } .two-col, .task-card, .recommend-card, .topic-card, .mini-row { grid-template-columns: 1fr; } .actions { justify-content: flex-start; } }</code>` | ????????????????? |
| 110 | `<code>@media (max-width: 460px) { .metric-grid { grid-template-columns: 1fr; } .calendar { gap: 5px; } .day-name, .day-cell { min-height: 38px; font-size: 13px; } }</code>` | ????????????????? |
