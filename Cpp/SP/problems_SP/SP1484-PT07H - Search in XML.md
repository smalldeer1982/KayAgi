---
title: "PT07H - Search in XML"
layout: "post"
diff: 难度0
pid: SP1484
tag: []
---

# PT07H - Search in XML

## 题目描述

XML（可扩展标记语言）正在成为互联网上一种流行的数据表示和交换标准。XML 通过文本形式来描述并运用树形结构来组织信息。一个标准的 XML 文档由嵌套的元素构成，其中一些可能带有属性和内容。但为简化这道题目，我们不考虑这些属性和内容，仅处理标签。一个元素通常由成对的标签构成，包括一个开始标签和一个结束标签。开始标签由尖括号包围的名字组成，如 `<tag>`，而结束标签是相同的名字但前面加上斜杠，如 `</tag>`。元素的内容可以为空或是位于开始标签与结束标签之间的其他子元素。特别地，每个 XML 元素的直接子元素中不会出现相同标签名的情况，即所有兄弟元素拥有不同的标签名称。以下是一个有效的 XML 文档示例：

```
<THU>
	<Team>
		<ACRush></ACRush>
		<Jelly></Jelly>
		<Cooly></Cooly>
	</Team>
	<JiaJia>
		<Team>
			<Ahyangyi></Ahyangyi>
			<Dragon></Dragon>
			<Cooly><Amber></Amber></Cooly>
		</Team>
	</JiaJia>
</THU>
```

为了便于识别文档中的元素，我们将根据元素开始标签在文档中出现的顺序对它们进行编号。例如，"THU" 编号为 1，第一个 "Team" 编号为 2，"ACRush" 编号为 3，"Ahyangyi" 编号为 8。

查询 XML 文档的问题吸引了许多研究者的注意。现在，我们有一个 XML 文档的查询模式和一个 XML 文本。以下是一个有效的查询模式示例：

`<Team><Cooly></Cooly></Team>`

我们需要找到此模式在 XML 文本中的所有出现位置。模式被认为在某个位置出现，当且仅当将模式的根元素放置在该位置时，模式中的每个元素都能与文本中的相同标签的元素匹配。由于兄弟元素的标签各不相同，因此在文本中放置模式只有一种方法。

## 输入格式

输入文件包含两个部分。第一部分是一个有效的 XML 文档，且恰好有一个根元素。第二部分是一个作为查询模式的有效 XML 文档，也恰好有一个根元素。请忽略输入文件中的所有空白字符（不可见字符），仅关注大写字母、小写字母以及 `/`、`<`、`>`。假设 XML 文档始终严格是一棵有根树。输入文件的大小小于 100kb。

## 输出格式

输出 XML 文本中查询模式的所有出现位置。第一行输出一个整数 $n$，表示查询模式出现的次数。接下来的 $n$ 行中，每行输出一个元素编号，表示此元素上出现了查询模式。请按照编号递增顺序输出。

 **本翻译由 AI 自动生成**

## 样例 #1

### 输入

```
&lt;THU>\n	&lt;Team>\n		&lt;ACRush>&lt;/ACRush>\n		&lt;Jelly>&lt;/Jelly>\n		&lt;Cooly>&lt;/Cooly>\n	&lt;/Team>\n	&lt;JiaJia>\n		&lt;Team>\n			&lt;Ahyangyi>&lt;/Ahyangyi>\n			&lt;Dragon>&lt;/Dragon>\n			&lt;Cooly>&lt;Amber>&lt;/Amber>&lt;/Cooly>\n		&lt;/Team>\n	&lt;/JiaJia>\n&lt;/THU>
&lt;Team>&lt;Cooly>&lt;/Cooly>&lt;/Team>
```

### 输出

```
2
2
7
```

