# -*- coding: utf-8 -*-
"""随机抽10张卡片人工目检。"""
import json, re, random, sqlite3, zipfile, os
APKG = r"F:\syncthing\考试\自考\13003数据结构与算法\ANKI\13003数据结构与算法-大纲考点.apkg"
TMP = r"F:\syncthing\考试\自考\13003数据结构与算法\ANKI\_build\verify_tmp"
with zipfile.ZipFile(APKG) as z:
    z.extract("collection.anki2", TMP)
con = sqlite3.connect(os.path.join(TMP, "collection.anki2"))
cur = con.cursor()
models = json.loads(cur.execute("SELECT models FROM col").fetchone()[0])
names = [f["name"] for f in list(models.values())[0]["flds"]]
rows = list(cur.execute("SELECT id, flds, tags FROM notes"))
con.close()
random.seed(42)
picks = random.sample(rows, 10)
for nid, flds, tags in picks:
    field = dict(zip(names, flds.split("\x1f")))
    front = re.sub(r"<[^>]+>", "", field["描述填空"]) if field["描述填空"] else "（题卡）" + re.sub(r"<[^>]+>", "", field["知识点"])
    back = re.sub(r"<[^>]+>", "", field["描述答案"]) if field["描述答案"] else "（无答案）"
    print("【%s】%s | 要求:%s | 小结:%s" % (field["章节"], field["知识点"], field["要求"], field["小结"]))
    print("  正面: %s" % front[:130])
    print("  反面: %s" % back[:130])
    print("  答案: %s | 页码: %s | 标签: %s" % (field["挖空答案"], field["页码"], " ".join(tags.split())))
    print()
