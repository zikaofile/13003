# -*- coding: utf-8 -*-
"""生成《13003数据结构与算法》Anki 知识库。

卡片设计（按用户要求）：
- 正面：D列知识点 + E列描述挖空版 + 以标签形式展示 A章节/B知识点要求/C章内小结
- 反面：E列完整描述（挖空处高亮）+ 挖空答案 + G列教材页码
- 真实 Anki 标签 = A章节 / B要求 / C小结（去空格），可按章节筛选复习
"""
import json
import random
import re
import html as _html
import csv as _csv

import genanki

ROWS = json.load(open(r"F:\syncthing\考试\自考\13003数据结构与算法\ANKI\_build\rows.json", encoding="utf-8"))

# ---------------------------------------------------------------- 常量
OUT_APKG = r"F:\syncthing\考试\自考\13003数据结构与算法\ANKI\13003数据结构与算法-大纲考点.apkg"
OUT_CSV = r"F:\syncthing\考试\自考\13003数据结构与算法\ANKI\13003数据结构与算法-导入用.csv"
MAX_BLANKS = 3

# 常见数据结构术语词典（配合 D 列知识点名共同作为挖空候选）
TERMS = """
栈顶 栈底 栈顶元素 栈底元素 入栈 出栈 栈顶指针 栈容量 链栈 顺序栈 共享栈
队头 队尾 入队 出队 循环队列 链队列 顺序队列 队满 队空 假溢出
线性表 顺序表 有序表 单链表 双链表 双向链表 循环链表 静态链表 头结点 头指针 尾指针
前驱 后继 直接前驱 直接后继 表长 表头 表尾
数组 多维数组 行主序 列主序 数组首地址 映射函数 一维数组 二维数组
广义表 长度 深度 表头 表尾 原子 子表 串 子串 主串 模式串 空白串 空格串 模式匹配 串长
树 子树 根结点 叶子结点 叶结点 结点的度 树的度 结点的层次 树的深度 森林 双亲 孩子 兄弟 堂兄弟
二叉树 满二叉树 完全二叉树 二叉排序树 平衡二叉树 二叉链表 三叉链表 线索二叉树 线索链表 先序遍历 中序遍历 后序遍历 层次遍历
哈夫曼树 最优二叉树 哈夫曼编码 带权路径长度 前缀编码 权值 路径长度
堆 大根堆 小根堆 堆顶 堆尾 优先队列 堆排序 筛选法建堆 上滤 下滤
图 顶点 边 弧 无向图 有向图 完全图 有向完全图 邻接点 度 入度 出度 连通图 连通分量 强连通图 强连通分量 子图 生成树 最小生成树 生成森林
邻接矩阵 邻接表 逆邻接表 十字链表 边集数组 深度优先搜索 广度优先搜索 普里姆算法 克鲁斯卡尔算法
拓扑排序 拓扑序列 关键路径 关键活动 事件的最早发生时间 事件的最迟发生时间 活动的弧头 源点 汇点 网 AOV网 AOE网 活动的最早开始时间 活动的最迟开始时间
排序 排序码 关键字 主关键字 次关键字 稳定性 内部排序 外部排序 直接插入排序 折半插入排序 希尔排序 冒泡排序 快速排序 简单选择排序 树形选择排序 锦标赛排序 堆排序 归并排序 二路归并 基数排序 分配排序 链式基数排序
时间复杂度 空间复杂度 平均时间复杂度 最坏情况 最好情况 平均情况 渐近时间复杂度
查找 静态查找表 动态查找表 顺序查找 折半查找 二分查找 分块查找 索引顺序查找 索引表 平均查找长度 ASL 二叉排序树 平衡因子 哈希表 散列表 哈希函数 散列函数 冲突 同义词 装填因子 开放定址法 线性探测 二次探测 再哈希 链地址法 伪随机探测
递归 迭代 分治 回溯 贪心 动态规划 循环 抽象数据类型 逻辑结构 存储结构 物理结构 数据元素 数据项 数据结构 算法 基本操作
""".split()

# ---------------------------------------------------------------- 文本清洗
CJK = r"\u4e00-\u9fff"
CJK_RE = re.compile("([%s])\\s+(?=[%s])" % (CJK, CJK))
DIGIT_RE = re.compile(r"(\d)\s+(?=\d)")


def clean_text(s):
    """轻量去 OCR 噪音：多空格折叠、中文字符间空格删除、数字间空格删除（前瞻式，可处理连续链）。"""
    s = s.replace("\r\n", "\n").replace("\r", "\n")
    s = re.sub(r"[ \t]+", " ", s)
    s = CJK_RE.sub(r"\1", s)
    s = DIGIT_RE.sub(r"\1", s)
    s = re.sub(r"\s+", " ", s)
    return s.strip()


def norm_term(s):
    """术语规范化：去空白与尾部标点。"""
    s = re.sub(r"\s+", "", s)
    return s.rstrip("。.，,；;：:、）)")


def build_term_pattern(term):
    """允许字符间有 0~1 个空格/制表符（兼容 OCR 噪音），不跨换行。"""
    return re.compile("".join(re.escape(c) + r"[ \t]*" for c in term))


# 合法术语字符（中文/字母，不含数字与符号），用于过滤 D 列进词典
TERM_OK = re.compile(r"^[\u4e00-\u9fffA-Za-z]{2,12}$")

# D 列全部知识点名 → 通用词典（每行挖空时排除该行自身的 D）
all_d = set()
for r in ROWS:
    t = norm_term(r["knowledge"])
    if TERM_OK.match(t):
        all_d.add(t)
COMMON_DICT = set(TERMS) | all_d
COMMON_DICT = {t for t in COMMON_DICT if TERM_OK.match(t)}

# 括号内英文别名
ALIAS_RE = re.compile(r"[（(]\s*([A-Za-z][A-Za-z ._-]{1,40}?)\s*[）)]")
# 引号短语
QUOTE_RE = re.compile(r"[“\"]([^”\"]{2,24})[”\"]")


def alias_ok(text):
    return (len(text) >= 2 and not re.search(r"\d|=|,|，|、|…|\.\.", text)
            and text.count(" ") <= 1)


def quote_ok(text):
    return "\n" not in text and len(text.strip()) >= 2


def find_first(pattern, text, start=0):
    m = pattern.search(text, start)
    return m


def collect_candidates(e, own_d):
    """返回候选 [(start, end, answer_text, kind)]，按优先级排序。"""
    cands = []
    for m in ALIAS_RE.finditer(e):
        alias = m.group(1).strip()
        if alias_ok(alias):
            cands.append((m.start(1), m.end(1), alias, "alias"))
    for m in QUOTE_RE.finditer(e):
        q = m.group(1).strip()
        if quote_ok(q):
            cands.append((m.start(1), m.end(1), q, "quote"))
    # 全部词典术语（含本行 D）首次出现位置：短术语若被更长术语覆盖则丢弃，
    # 避免把"数据"挖进"数据元素"、把"排序"挖进"堆排序"这类半词错误。
    allm = []
    for t in sorted(COMMON_DICT, key=len):
        if len(t) < 2:
            continue
        m = build_term_pattern(t).search(e)
        if m:
            allm.append((m.start(0), m.end(0), t, t == own_d))
    kept = []
    for i, (s, e2, t, is_own) in enumerate(allm):
        if any(s2 <= s and e2_ >= e2 and len(t2) > len(t)
               for j, (s2, e2_, t2, _) in enumerate(allm) if j != i):
            continue
        kept.append((s, e2, t, is_own))
    for s, e2, t, is_own in kept:
        if is_own:
            continue
        if any(s <= b and e2 >= a for a, b, _, _ in cands):
            continue
        cands.append((s, e2, t, "term"))
    # 按 (span长度降序, 优先级) 稳定排序，避免同词重复
    cands.sort(key=lambda c: (-(c[1] - c[0]), {"alias": 0, "quote": 1, "term": 2}[c[3]]))
    return cands


def pick_blanks(cands, e):
    """挑出互不重叠的至多 MAX_BLANKS 个挖空点。"""
    chosen = []
    for a, b, ans, kind in cands:
        if len(chosen) >= MAX_BLANKS:
            break
        if any(not (b <= x or a >= y) for x, y, _, _ in chosen):
            continue
        chosen.append((a, b, ans, kind))
    return chosen


def build_html(e, chosen):
    """生成：正面填空版 + 反面完整版(挖空处高亮) + 挖空答案列表。

    e: 清洗后的描述文本；chosen: [(start,end,answer,kind)]
    返回 (front_html, back_html, answers_line, has_blank)
    """
    if not e:
        return "", "", "", False

    # --- 正面：挖空处替换为 ______（按出现位置排序，答案顺序与之对应） ---
    spans = sorted(chosen, key=lambda c: c[0])
    parts = []
    pos = 0
    for a, b, ans, kind in spans:
        parts.append(_html.escape(e[pos:a]))
        parts.append('<span class="blank">______</span>')
        pos = b
    parts.append(_html.escape(e[pos:]))
    front = "".join(parts)

    # --- 反面：所有被挖答案的出现处高亮（长答案优先，避免嵌套/重叠） ---
    hit_spans = []
    for a, b, ans, kind in chosen:
        pat = build_term_pattern(ans) if kind in ("term",) else re.compile(
            re.escape(ans) if kind == "alias" else re.escape(ans))
        for m in pat.finditer(e):
            hit_spans.append((m.start(), m.end(), ans))
    hit_spans.sort(key=lambda s: (-(s[1] - s[0]), s[0]))
    kept = []
    for a, b, ans in hit_spans:
        if any(not (b <= x or a >= y) for x, y, _ in kept):
            continue
        kept.append((a, b, ans))
    kept.sort()
    parts = []
    pos = 0
    for a, b, ans in kept:
        parts.append(_html.escape(e[pos:a]))
        parts.append('<span class="hit">%s</span>' % _html.escape(ans))
        pos = b
    parts.append(_html.escape(e[pos:]))
    back = "".join(parts)

    answers = "、".join(a for _, _, a, _ in spans)
    return front, back, answers, bool(chosen)


# ---------------------------------------------------------------- Anki 模型
MODEL_ID = 1300317000001
DECK_ID = 1300317000002

css = """
.card { font-family: "Microsoft YaHei","PingFang SC","Noto Sans SC",sans-serif;
  font-size:17px; line-height:1.75; color:#222; }
.top { margin-bottom:12px; }
.chip { display:inline-block; font-size:12px; padding:2px 12px; border-radius:12px; margin:2px 6px 2px 0; }
.c1 { background:#e3f2fd; color:#1565c0; }
.c2 { background:#e8f5e9; color:#2e7d32; }
.c3 { background:#fff3e0; color:#e65100; }
h1 { font-size:20px; color:#0d47a1; border-bottom:2px solid #e3e3e3; padding-bottom:6px; margin:6px 0 12px; }
.q { background:#f4f7fb; padding:12px 14px; border-radius:8px; border-left:4px solid #1565c0; }
.blank { color:#c62828; font-weight:bold; text-decoration:underline dotted #c62828; }
.a { background:#f4fbf5; padding:12px 14px; border-radius:8px; border-left:4px solid #2e7d32; }
.hit { color:#c62828; font-weight:bold; background:#ffecec; padding:0 3px; border-radius:3px; }
.ansbox { background:#fff8e1; padding:6px 12px; border-radius:6px; color:#795548;
  font-size:14px; margin-top:10px; border:1px dashed #e6c66b; }
.ansbox b { color:#c62828; }
.pg { margin-top:10px; font-size:13px; color:#8a8a8a; }
.note { color:#9e9e9e; font-size:14px; font-style:italic; }
"""

FRONT_TPL = """
<div class="top">
  {{#章节}}<span class="chip c1">章节：{{章节}}</span>{{/章节}}
  {{#要求}}<span class="chip c2">{{要求}}</span>{{/要求}}
  {{#小结}}<span class="chip c3">{{小结}}</span>{{/小结}}
</div>
{{#知识点}}<h1>{{知识点}}</h1>{{/知识点}}
{{#描述填空}}<div class="q">{{描述填空}}</div>{{/描述填空}}
"""

BACK_TPL = """
<div class="top">
  {{#章节}}<span class="chip c1">章节：{{章节}}</span>{{/章节}}
  {{#要求}}<span class="chip c2">{{要求}}</span>{{/要求}}
  {{#小结}}<span class="chip c3">{{小结}}</span>{{/小结}}
</div>
{{#知识点}}<h1>{{知识点}}</h1>{{/知识点}}
{{#描述答案}}<div class="a">{{描述答案}}</div>{{/描述答案}}
{{^描述答案}}<div class="note">{{#知识点}}（大纲未提供该知识点描述，请查阅教材对应页码）{{/知识点}}{{^知识点}}（大纲未提供该题答案，请对照教材核对）{{/知识点}}</div>{{/描述答案}}
{{#挖空答案}}<div class="ansbox">挖空答案：<b>{{挖空答案}}</b></div>{{/挖空答案}}
{{#页码}}<div class="pg">教材页码：P{{页码}}</div>{{/页码}}
"""

model = genanki.Model(
    MODEL_ID,
    "13003大纲考点卡",
    fields=[
        {"name": "章节"},
        {"name": "要求"},
        {"name": "小结"},
        {"name": "知识点"},
        {"name": "描述填空"},
        {"name": "描述答案"},
        {"name": "挖空答案"},
        {"name": "页码"},
    ],
    templates=[
        {
            "name": "大纲考点卡",
            "qfmt": FRONT_TPL,
            "afmt": BACK_TPL,
        }
    ],
    css=css,
)

deck = genanki.Deck(DECK_ID, "13003数据结构与算法")


def sanitize_tag(s):
    return re.sub(r"\s+", "", s)


# ---------------------------------------------------------------- 生成卡片
notes = []
stats = {"total": 0, "with_desc": 0, "no_desc": 0, "with_blank": 0,
         "no_blank": 0, "skipped_no_knowledge": 0, "blank_count": {}}

for r in ROWS:
    d = norm_term(r["knowledge"])
    if not d:
        if r["desc"].strip():
            stats["skipped_no_knowledge"] += 1
        continue
    stats["total"] += 1

    chapter = clean_text(r["chapter"])
    req = clean_text(r["requirement"])
    summ = clean_text(r["summary"])
    e = clean_text(r["desc"])
    page = r["page"]

    front_desc, back_desc, answers, has_blank = "", "", "", False
    if e:
        stats["with_desc"] += 1
        cands = collect_candidates(e, d)
        chosen = pick_blanks(cands, e)
        if not chosen:
            # 保底挖空：该行自身 D 术语首次出现
            p = build_term_pattern(d)
            m = p.search(e)
            if m:
                chosen = [(m.start(0), m.end(0), d, "term")]
        front_desc, back_desc, answers, has_blank = build_html(e, chosen)
        if has_blank:
            stats["with_blank"] += 1
            stats["blank_count"][len(chosen)] = stats["blank_count"].get(len(chosen), 0) + 1
        else:
            stats["no_blank"] += 1
    else:
        stats["no_desc"] += 1
        # 无描述：若 D 是长题干（课后习题），转为"题卡"：正面显示题干
        if len(d) > 24:
            front_desc = norm_term(d)
            d = ""

    tags = [sanitize_tag(chapter), sanitize_tag(req), sanitize_tag(summ), "13003数据结构与算法"]
    tags = [t for t in tags if t]

    page_str = str(int(page)) if isinstance(page, (int, float)) and page is not None else (str(page).strip() if page else "")

    note = genanki.Note(
        model=model,
        fields=[chapter, req, summ, d, front_desc, back_desc, answers, page_str],
        tags=tags,
        guid=genanki.guid_for(str(r["excel_row"]), d, e[:40]),
    )
    notes.append(note)

# 同一行号不会重复；guid 唯一性校验
guids = [n.guid for n in notes]
assert len(guids) == len(set(guids)), "guid 冲突"

for n in notes:
    deck.add_note(n)
pkg = genanki.Package(deck)
pkg.write_to_file(OUT_APKG)


def csv_chips(ch, req, summ):
    parts = []
    if ch:
        parts.append('<span class="chip c1">章节：%s</span>' % _html.escape(ch))
    if req:
        parts.append('<span class="chip c2">%s</span>' % _html.escape(req))
    if summ:
        parts.append('<span class="chip c3">%s</span>' % _html.escape(summ))
    return '<div class="top">%s</div>' % "".join(parts) if parts else ""


# ---------------------------------------------------------------- CSV 备份
with open(OUT_CSV, "w", encoding="utf-8-sig", newline="") as f:
    w = _csv.writer(f, delimiter="\t")
    w.writerow(["Front", "Back", "Tags"])
    for n in notes:
        ch, req, summ, d, front_desc, back_desc, answers, page = n.fields
        head = csv_chips(ch, req, summ) + (("<h1>%s</h1>" % _html.escape(d)) if d else "")
        front_html = head
        if front_desc:
            front_html += '<div class="q">%s</div>' % front_desc
        back_html = head
        if back_desc:
            back_html += '<div class="a">%s</div>' % back_desc
        else:
            note = "（大纲未提供该题答案，请对照教材核对）" if not d else "（大纲未提供该知识点描述，请查阅教材对应页码）"
            back_html += '<div class="note">%s</div>' % note
        if answers:
            back_html += '<div class="ansbox">挖空答案：<b>%s</b></div>' % _html.escape(answers)
        if page:
            back_html += '<div class="pg">教材页码：P%s</div>' % _html.escape(page)
        w.writerow([front_html, back_html, " ".join(n.tags)])

print("卡片总数:", stats["total"])
print("含描述:", stats["with_desc"], "| 无描述(只有知识点):", stats["no_desc"])
print("含挖空:", stats["with_blank"], "| 无挖空:", stats["no_blank"])
print("挖空数分布:", stats["blank_count"])
print("跳过(有E无D):", stats["skipped_no_knowledge"])
print("已写出:", OUT_APKG)
print("已写出:", OUT_CSV)
