---
title: "PLAYFAIR - Playfair Cracker"
layout: "post"
diff: 难度0
pid: SP4476
tag: []
---

# PLAYFAIR - Playfair Cracker

## 题目描述

在本题中，你需要破解 Playfair 密码，判断是存在多个解，还是没有解。

具体规则如下：

1. 将文本中的所有字母转换为大写，并移除所有非字母字符。
2. 将所有 'J' 换成 'I'。
3. 将字母成对组合成双字母组（digraphs），尽量避免在同一个双字母组中出现相同的字母。如果有必要，在相同字母间插入一个额外的 'X'。如果重复的字母是 'X'，就插入 'Q'。
4. 如果最后一个双字母组少一个字母，就在文本末尾补一个 'X'（如果最后一个字母是 'X'，则补 'Q'）。

以这段信息为例：“Programming in C and Pascal is easy; I will learn Java next year.” 转换后的双字母组为：

PR OG RA MX MI NG IN CA ND PA SC AL IS EA SY IW IL LX LE AR NI AV AN EX TY EA RX

注意在 "programming" 中两个 'M' 之间插入了 'X'，而在 "will" 中的两个 'L'因为在不同的双字母组中，所以没有插入 'X'，但在 "will" 和 "learn" 之间加了一个 'X'。末尾也加了一个 'X'。在 "Java" 中的 'J' 变成了 'I'。

再看另一个例子，信息为：“I am an ex-xenophobe, attempting to relax!”会变成：

IA MA NE XQ XE NO PH OB EA TX TE MP TI NG TO RE LA XQ

下一步是按照以下规则将每个双字母组转换为另一个双字母组：

在 5×5 的方格中按某一预定顺序排列大写字母（不包含 'J'），这是加密的密钥。

- 如果双字母组中的两个字母在同一行，将它们替换为各自右边的字母。如果某个字母在最右列，则用同一行的第一列字母替代（循环回到开头）。
- 如果双字母组中的两个字母在同一列，将它们替换为其下方的字母。若某个字母在最后一行，则用同一列的第一行字母替代（循环至顶部）。
- 如果这两个字母既不在同一行也不在同一列，则第一个字母替换为与它同行但与第二个字母同列的字母，第二个字母则替换为与它同行但与第一个字母同列的字母。

这些转换后的双字母组即是加密后的代码。

## 输入格式

输入包含若干组数据，第一行给出组数。每组数据由三个部分组成。第一部分是明文，由一行或多行普通文本构成。第二部分是对应的加密代码。第三部分是需要你解密的代码。每一部分用一行仅包含一个井号（'#'）分隔。代码部分以大写的双字母组形式展示，每行最多包含 20 个双字母组，之间用空格分隔。代码部分的最后一行可能少于 100 个双字母组。每个代码部分最多包含 5000 个双字母组。

## 输出格式

对于每组数据，首先输出一行 "Case x:"，其中 x 是数据组编号（从 1 开始）。接下来，按输入时代码部分的格式输出解密后的代码。如果有多个解，则在一行中输出 "MULTIPLE SOLUTIONS"。如果没有解，则在一行中输出 "NO SOLUTIONS"。各组数据之间用空行隔开。

 **本翻译由 AI 自动生成**

## 样例 #1

### 输入

```
2\nProgramming in C and Pascal is easy; I will learn Java next year.\n#\nFV CV GE PH PW AS UX GL UY ZX GY LZ UV HE NS UI UQ IA QA EG\nXU XG EA HN KC HE VE\n#\nLX ZH AH EI NH XY MX KV HE OE RQ PD OQ AS KY EQ ZL EI\n#\nIt is full moon!\nMeet me at Hammersmith Bridge tonight.\n#\nMP PI NZ AZ RN QV UG GD DO GD RQ AR KY GD HD NK PR DA MS OG\nUP GK IC QY\n#\nHL WT UP MC HQ RW PI CX DC ZD HB HG KL PM GI FP SK GE QR MF\nMP AR BH HM HA SP DP TC WM DZ PO RL SG MU DC SB OD SM MU CS\nUH RX BL MH HG WS DC BH MF KR MZ GT CD PU CS HD GH LK DP CT\nGI RZ CD EV KY GD MF IP GT IF KG IC EH TE SD QV QG PR RQ EV\nMU HK IF RC CR EQ OU PR SB GE CD PR PI UP DR UE EV FS BH MF\nEV FS DA BC MK GI\n#\n
\n
```

### 输出

```
Case 1:\nIA MA NE XQ XE NO PH OB EA TX TE MP TI NG TO RE LA XQ\n\nCase 2:\nCR YP TO GR AP HY IS AV ER YF AS CI NA TI NG SU BI EC TA ND\nIT HA SA RI CH HI ST OR YI FY OU AR EI NT ER ES TE DI NT HE\nPL AY FA IR CI PH ER SA ND MA NY MO RE OT HE RS IC AN ST RO\nNG LY RE CO MX ME ND SI MO NS IN GH SC OD EB OX OK TH AT CO\nNT AI NS AL LA BO UT TH ES EC RE TH IS TO RY OF CO DE SA ND\nCO DE BR EA KI NG\n\n
```

