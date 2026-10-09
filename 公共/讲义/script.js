(function () {
  var root = document.getElementById("root");
  var ring = root.getAttribute("data-ring");             // 目录页没有
  var secs = Array.prototype.slice.call(document.querySelectorAll(".recall, .sec"));

  function load(k) { try { return JSON.parse(localStorage.getItem(k)); } catch (e) { return null; } }
  function save(k, v) { try { localStorage.setItem(k, JSON.stringify(v)); } catch (e) {} }
  function label(s) {
    if (s.classList.contains("recall")) return "开始之前";
    return s.dataset.short || "";
  }

  /* 图标：Lucide（github.com/lucide-icons/lucide，ISC 许可），24×24 线条图标，内联才能离线用 */
  var IC = {
    code: '<path d="m18 16 4-4-4-4"/><path d="m6 8-4 4 4 4"/><path d="m14.5 4-5 16"/>',
    bulb: '<path d="M15 14c.2-1 .7-1.7 1.5-2.5 1-.9 1.5-2.2 1.5-3.5A6 6 0 0 0 6 8c0 1 .2 2.2 1.5 3.5.7.7 1.3 1.5 1.5 2.5"/><path d="M9 18h6"/><path d="M10 22h4"/>',
    history: '<path d="M3 12a9 9 0 1 0 9-9 9.75 9.75 0 0 0-6.74 2.74L3 8"/><path d="M3 3v5h5"/><path d="M12 7v5l4 2"/>',
    target: '<circle cx="12" cy="12" r="10"/><circle cx="12" cy="12" r="6"/><circle cx="12" cy="12" r="2"/>',
    alert: '<path d="m21.73 18-8-14a2 2 0 0 0-3.48 0l-8 14A2 2 0 0 0 4 21h16a2 2 0 0 0 1.73-3"/><path d="M12 9v4"/><path d="M12 17h.01"/>',
    copy: '<rect width="14" height="14" x="8" y="8" rx="2" ry="2"/><path d="M4 16c-1.1 0-2-.9-2-2V4c0-1.1.9-2 2-2h10c1.1 0 2 .9 2 2"/>',
    check: '<path d="M20 6 9 17l-5-5"/>',
    left: '<path d="m12 19-7-7 7-7"/><path d="M19 12H5"/>',
    up: '<path d="m5 12 7-7 7 7"/><path d="M12 19V5"/>',
    list: '<path d="M3 12h.01"/><path d="M3 18h.01"/><path d="M3 6h.01"/><path d="M8 12h13"/><path d="M8 18h13"/><path d="M8 6h13"/>',
    eye: '<path d="M2.062 12.348a1 1 0 0 1 0-.696 10.75 10.75 0 0 1 19.876 0 1 1 0 0 1 0 .696 10.75 10.75 0 0 1-19.876 0"/><circle cx="12" cy="12" r="3"/>',
    eyeoff: '<path d="M10.733 5.076a10.744 10.744 0 0 1 11.205 6.575 1 1 0 0 1 0 .696 10.747 10.747 0 0 1-1.444 2.49"/><path d="M14.084 14.158a3 3 0 0 1-4.242-4.242"/><path d="M17.479 17.499a10.75 10.75 0 0 1-15.417-5.151 1 1 0 0 1 0-.696 10.75 10.75 0 0 1 4.446-5.143"/><path d="m2 2 20 20"/>',
    layers: '<path d="m12.83 2.18a2 2 0 0 0-1.66 0L2.6 6.08a1 1 0 0 0 0 1.83l8.58 3.91a2 2 0 0 0 1.66 0l8.58-3.9a1 1 0 0 0 0-1.83Z"/><path d="m22 17.65-9.17 4.16a2 2 0 0 1-1.66 0L2 17.65"/><path d="m22 12.65-9.17 4.16a2 2 0 0 1-1.66 0L2 12.65"/>',
    repeat: '<path d="m17 2 4 4-4 4"/><path d="M3 11v-1a4 4 0 0 1 4-4h14"/><path d="m7 22-4-4 4-4"/><path d="M21 13v1a4 4 0 0 1-4 4H3"/>',
    book: '<path d="M2 3h6a4 4 0 0 1 4 4v14a3 3 0 0 0-3-3H2z"/><path d="M22 3h-6a4 4 0 0 0-4 4v14a3 3 0 0 1 3-3h7z"/>',
    compass: '<circle cx="12" cy="12" r="10"/><polygon points="16.24 7.76 14.12 14.12 7.76 16.24 9.88 9.88 16.24 7.76"/>',
    term: '<polyline points="4 17 10 11 4 5"/><line x1="12" x2="20" y1="19" y2="19"/>'
  };
  function ic(n) { return '<svg class="ic" viewBox="0 0 24 24" aria-hidden="true">' + IC[n] + "</svg>"; }

  /* 给各种块加图标、给代码块加标题栏 */
  var PART_IC = { p1: "code", p2: "bulb", rings: "layers", base: "repeat", cover: "book", how: "compass" };
  var parts = document.querySelectorAll(".part");
  parts.forEach(function (p, i) {
    var sp = document.createElement("span");
    sp.className = "pic"; sp.innerHTML = ic(PART_IC[p.id] || (i ? "bulb" : "code"));
    p.insertBefore(sp, p.firstChild);
  });
  document.querySelectorAll(".exam > p:first-child").forEach(function (p) { p.innerHTML = ic("target") + p.innerHTML; });
  document.querySelectorAll(".fix").forEach(function (f) {
    var t = document.createElement("span"); t.className = "ft"; t.innerHTML = ic("alert") + "注意";
    f.insertBefore(t, f.firstChild);
  });
  document.querySelectorAll(".recall h2").forEach(function (h) { h.innerHTML = ic("history") + h.innerHTML; });
  document.querySelectorAll(".code").forEach(function (box) {
    var hd = document.createElement("div"), isOut = !!box.querySelector("pre.o");
    hd.className = "hd";
    hd.innerHTML = '<span class="dots"><i></i><i></i><i></i></span>' + (isOut ? ic("term") + "输出" : ic("code") + (box.dataset.label || "C"));
    box.insertBefore(hd, box.firstChild);
  });
  /* 第二部分（细节）的节，目录高亮用紫色 */
  var inP2 = false;
  document.querySelectorAll(".part, .sec").forEach(function (el) {
    if (el.classList.contains("part")) { inP2 = el !== parts[0]; return; }
    if (inP2) el.classList.add("p2");
  });

  /* 目录：大部分做小标题，每一节一行 */
  function buildToc(nav, withHome) {
    if (!nav) return;
    var h = "";
    if (withHome && ring) h += '<a class="home" href="' + root.getAttribute("data-home") + '">' + ic("left") + "全部 13 环</a>";
    document.querySelectorAll(".recall, .part, .sec").forEach(function (s) {
      if (s.classList.contains("part")) h += "<p>" + s.querySelector("h2").textContent + "</p>";
      else if (label(s)) h += '<a href="#' + s.id + '" data-id="' + s.id + '"' + (s.classList.contains("p2") ? ' class="p2"' : "") + ">" + label(s) + "</a>";
    });
    nav.innerHTML = h;
  }
  buildToc(document.getElementById("toc"), true);
  buildToc(document.getElementById("toc-m"), false);
  buildToc(document.getElementById("toc-d"), true);
  document.querySelectorAll("#toc-m a").forEach(function (a) {
    a.addEventListener("click", function () { a.closest("details").open = false; });
  });

  /* 空：点一下揭开 */
  function hidden() { return root.classList.contains("hide"); }
  document.querySelectorAll(".a").forEach(function (a) {
    function flip() { if (hidden()) { a.classList.toggle("on"); syncSec(a.closest(".sec, .recall")); } }
    a.setAttribute("role", "button");
    a.setAttribute("aria-label", "点开看答案");
    a.addEventListener("click", flip);
    a.addEventListener("keydown", function (e) { if (e.key === "Enter" || e.key === " ") { e.preventDefault(); flip(); } });
  });
  document.querySelectorAll(".oa").forEach(function (o) {
    function flip() { if (hidden()) { o.classList.toggle("on"); syncSec(o.closest(".sec, .recall")); } }
    o.addEventListener("click", function (e) { if (!e.target.closest(".copy")) flip(); });
    o.addEventListener("keydown", function (e) { if (e.key === "Enter") { e.preventDefault(); flip(); } });
  });

  /* 每节一个「本节答案」：一次揭开这一节的全部空 */
  function blanks(s) { return s ? s.querySelectorAll(".a, .oa") : []; }
  function syncSec(s) {
    if (!s || !s._btn) return;
    var all = blanks(s), open = 0;
    for (var i = 0; i < all.length; i++) if (all[i].classList.contains("on")) open++;
    var allOpen = open === all.length;
    s._btn.dataset.open = allOpen ? "1" : "";
    s._btn.innerHTML = allOpen ? ic("eyeoff") + "盖上本节" : ic("eye") + "本节答案";
    s._btn.hidden = !hidden();
  }
  secs.forEach(function (s) {
    var head = s.querySelector("h3, h2");
    if (!head || !blanks(s).length) return;
    var b = document.createElement("button");
    b.type = "button"; b.className = "secbtn";
    b.addEventListener("click", function () {
      var all = blanks(s), allOpen = b.dataset.open === "1";
      for (var i = 0; i < all.length; i++) all[i].classList.toggle("on", !allOpen);
      syncSec(s);
    });
    head.appendChild(b);
    s._btn = b;
    syncSec(s);
  });

  /* 全部揭开 / 盖上 */
  /* 每道题的完整程序：点一下展开 / 收起 */
  document.querySelectorAll(".prog-btn").forEach(function (b) {
    b.innerHTML = ic("code") + "完整程序";
    b.addEventListener("click", function () {
      var on = b.parentNode.classList.toggle("on");
      b.setAttribute("aria-expanded", on ? "true" : "false");
      b.innerHTML = ic("code") + (on ? "收起程序" : "完整程序");
    });
  });
  var btn = document.getElementById("toggle");
  function toggleAll() {
    if (!btn) return;
    var h = root.classList.toggle("hide");
    document.querySelectorAll(".a.on, .oa.on, .prog.on").forEach(function (a) { a.classList.remove("on"); });
    document.querySelectorAll(".prog-btn").forEach(function (b) { b.setAttribute("aria-expanded", "false"); b.innerHTML = ic("code") + "完整程序"; });
    btn.innerHTML = h ? ic("eye") + "全部揭开" : ic("eyeoff") + "全部盖上";
    btn.setAttribute("aria-pressed", h ? "false" : "true");
    secs.forEach(syncSec);
  }
  if (btn) { btn.innerHTML = ic("eye") + "全部揭开"; btn.addEventListener("click", toggleAll); }

  /* 当前读到哪一节：目录高亮，并记下来，下次打开可以接着读 */
  var current = null;
  function setCurrent(s) {
    if (current === s) return;
    current = s;
    document.querySelectorAll(".toc a[data-id]").forEach(function (a) { a.classList.toggle("cur", a.dataset.id === s.id); });
    if (ring) {
      save("c-lesson-pos-" + ring, s.id);
      save("c-lesson-last", { ring: ring, name: root.getAttribute("data-name"), sec: label(s) });
    }
  }
  if ("IntersectionObserver" in window) {
    var io = new IntersectionObserver(function (es) {
      es.forEach(function (e) { if (e.isIntersecting) setCurrent(e.target); });
    }, { rootMargin: "-15% 0px -75% 0px" });
    secs.forEach(function (s) { io.observe(s); });
  }

  /* 上次读到哪：给一个「继续」 */
  var resume = document.getElementById("resume");
  if (resume && ring && !location.hash) {
    var pos = load("c-lesson-pos-" + ring), target = pos && document.getElementById(pos);
    if (target && secs.indexOf(target) > 1) {
      resume.innerHTML = '<span>上次读到</span><a href="#' + pos + '">' + label(target) + ' →</a><button type="button">不用了</button>';
      resume.classList.add("on");
      resume.querySelector("a").addEventListener("click", function () { resume.classList.remove("on"); });
      resume.querySelector("button").addEventListener("click", function () { resume.classList.remove("on"); });
    }
  }
  /* 目录页：标出上次看的那一环 */
  if (!ring) {
    var last = load("c-lesson-last");
    if (last && last.ring) {
      var li = document.querySelector('.rings li[data-ring="' + last.ring + '"]');
      if (li) {
        li.classList.add("last");
        if (last.sec) {
          var p = document.createElement("p");
          p.textContent = "上次读到：" + last.sec;
          p.style.color = "var(--green)";
          li.appendChild(p);
        }
      }
    }
  }

  /* 阅读进度条、浮动按钮 */
  var bar = document.getElementById("progress"), fab = document.getElementById("fab"), ticking = false;
  function onScroll() {
    var h = document.documentElement.scrollHeight - window.innerHeight;
    if (bar) bar.style.width = (h > 0 ? Math.min(100, window.scrollY / h * 100) : 0) + "%";
    if (fab) fab.classList.toggle("on", window.scrollY > 500);
    ticking = false;
  }
  window.addEventListener("scroll", function () { if (!ticking) { ticking = true; requestAnimationFrame(onScroll); } }, { passive: true });
  onScroll();
  var drawer = document.getElementById("drawer");
  function closeDrawer() { if (drawer) drawer.classList.remove("on"); }
  var top = document.getElementById("fab-top");
  if (top) top.innerHTML = ic("up");
  if (document.getElementById("fab-toc")) document.getElementById("fab-toc").innerHTML = ic("list");
  if (top) top.addEventListener("click", function () { window.scrollTo({ top: 0 }); });
  var ft = document.getElementById("fab-toc");
  if (ft) ft.addEventListener("click", function () {
    drawer.classList.add("on");
    var cur = drawer.querySelector("a.cur");
    if (cur) cur.scrollIntoView({ block: "center" });
  });
  if (drawer) {
    drawer.querySelector(".shade").addEventListener("click", closeDrawer);
    drawer.querySelectorAll("a").forEach(function (a) { a.addEventListener("click", closeDrawer); });
  }

  /* 键盘：J 下一节，K 上一节，A 全部揭开 / 盖上，Esc 关目录 */
  document.addEventListener("keydown", function (e) {
    if (e.ctrlKey || e.metaKey || e.altKey) return;
    var t = e.target.tagName;
    if (t === "INPUT" || t === "TEXTAREA") return;
    if (e.key === "Escape") { closeDrawer(); return; }
    var k = e.key.toLowerCase();
    if ((k === "j" || k === "k") && secs.length) {
      var i = current ? secs.indexOf(current) : -1;
      var n = secs[Math.max(0, Math.min(secs.length - 1, i + (k === "j" ? 1 : -1)))];
      if (n) { n.scrollIntoView({ behavior: "instant", block: "start" }); setCurrent(n); }
    } else if (k === "a" && btn) {
      toggleAll();
    }
  });

  /* C 代码着色 */
  var KW = /^(int|double|float|char|long|short|unsigned|signed|void|return|for|while|do|if|else|switch|case|break|continue|sizeof|struct|union|enum|typedef|static|extern|register|auto|const|default|goto|FILE|NULL|EOF)$/;
  function esc(s) { return s.replace(/&/g, "&amp;").replace(/</g, "&lt;").replace(/>/g, "&gt;"); }
  function hl(src) {
    var out = "", re = /(\/\/[^\n]*|\/\*[\s\S]*?\*\/)|("(?:\\.|[^"\\\n])*"|'(?:\\.|[^'\\\n])*')|(^[ \t]*#[^\n]*)|(\b\d+(?:\.\d*)?(?:[eE][-+]?\d+)?[fFlL]?\b)|([A-Za-z_]\w*)/gm, m, last = 0;
    while ((m = re.exec(src))) {
      out += esc(src.slice(last, m.index));
      var t = m[0];
      if (m[1]) out += '<span class="t-com">' + esc(t) + "</span>";
      else if (m[2]) out += '<span class="t-str">' + esc(t) + "</span>";
      else if (m[3]) out += '<span class="t-pre">' + esc(t) + "</span>";
      else if (m[4]) out += '<span class="t-num">' + esc(t) + "</span>";
      else if (KW.test(t)) out += '<span class="t-kw">' + t + "</span>";
      else out += esc(t);
      last = re.lastIndex;
    }
    return out + esc(src.slice(last));
  }
  document.querySelectorAll("pre code.c").forEach(function (c) { c.innerHTML = hl(c.textContent); });

  /* 复制：方便贴进 草稿.c 自己跑 */
  document.querySelectorAll(".code").forEach(function (box) {
    var pre = box.querySelector("pre"), b = document.createElement("button");
    b.type = "button"; b.className = "copy"; b.innerHTML = ic("copy") + "复制";
    b.addEventListener("click", function (e) {
      e.stopPropagation();
      function done(msg) { b.innerHTML = ic("check") + msg; setTimeout(function () { b.innerHTML = ic("copy") + "复制"; }, 1400); }
      function fallback() {
        var r = document.createRange(); r.selectNodeContents(pre);
        var sel = window.getSelection(); sel.removeAllRanges(); sel.addRange(r);
        done("已选中，按 Ctrl+C");
      }
      try { navigator.clipboard.writeText(pre.textContent).then(function () { done("已复制"); }, fallback); }
      catch (err) { fallback(); }
    });
    (box.querySelector(".hd") || box).appendChild(b);
  });
})();
