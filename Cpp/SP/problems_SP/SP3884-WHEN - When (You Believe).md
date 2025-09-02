---
title: "WHEN - When (You Believe)"
layout: "post"
diff: 难度0
pid: SP3884
tag: []
---

# WHEN - When (You Believe)

## 题目描述

相信就会有奇迹。下面这门编程语言展示了“when”的强大。它有着简单而直观的（大小写不敏感）语法：

```
PROGRAM := WHEN | PROGRAM WHEN
WHEN := ‘when’ EXPRESSION <ENTER> STATEMENTS ‘end when’ <ENTER>
STATEMENTS := STATEMENT | STATEMENTS STATEMENT
STATEMENT := PRINT | SET
PRINT := ‘print’ EXPRESSION_LIST <ENTER>
SET := ‘set’ ASSIGNMENT_LIST <ENTER>
EXPRESSION_LIST := EXPRESSION | EXPRESSION_LIST ‘,’ EXPRESSION
ASSIGNMENT_LIST := ASSIGNMENT | ASSIGNMENT_LIST ‘,’ ASSIGNMENT
ASSIGNMENT := VARIABLE ‘=’ EXPRESSION
EXPRESSION := ‘(’ EXPRESSION OP EXPRESSION ‘)’ | VARIABLE | NUMBER 
OP := ‘<’ | ‘+’ | ‘-’ | ‘and’ | ‘or’ | ‘xor’
VARIABLE := ‘$’ NOT_DOLLAR_STRING ‘$’
NUMBER := DIGIT | NUMBER DIGIT
DIGIT := ‘0’ | .. | ‘9’
NOT_DOLLAR_STRING := 不能含有 $ 符号的任意可打印字符序列（含空格）
```

上面用单引号标注的内容需要按字面量处理；<ENTER> 表示行末。

简单来说，除了数字内部，任何字面量的两侧都允许有空格。变量名中可以出现空格，且每个非空的空格序列会被视为一个下划线。因此以下各个变量名是等同的：

```
$Remote Switch#1$
$Remote_Switch#1$
$Remote   switch#1$
```

程序中的数字均为 0 至 1000000000 之间的整数，变量及字面量的值介于 -1000000000 和 1000000000 之间。所有变量为全局变量，初始值为 0。所有测试程序中的表达式一定在有效值域范围内。逻辑运算符的结果为 0（假）或 1（真），且视任何非零值为真。

程序运行时，所有激活的 when 子句会被执行，直至无子句可执行。具体执行过程如下：

- 按顺序评估程序中所有未激活的 when 子句的条件。如果条件为真，该子句被加入活动列表末尾，并标记其第一个语句为“就绪”。每个活动的 when 子句始终有一个“就绪”语句。
- 若完成此步后活动列表为空，程序即终止。
- 执行“当前”when 子句（初始为活动列表中的第一个子句）的“就绪”语句。
- 将标记为“就绪”的语句更新。如果该语句为“当前”when 子句的最后一个语句，则从活动列表中移除该子句。
- 将“当前”子句标记更新。如果活动列表已到达末尾，则回到开头继续。

更简单地说，就是评估未激活的 when 条件，以决定是否将其加入活动列表。随后，从当前活动的 when 子句中执行一个语句（set 或 print）。若该子句没有更多语句可执行，则其将被移出活动列表。在下一循环中，将从下一个活动的 when 子句中执行一个语句，依此类推。

set 语句可以同时执行多个赋值操作，因此

```
set $x$=$y$,$y$=$x$
```

将 $x$ 和 $y$ 的值对调。同一个 set 语句中不能重复赋值同一变量（例如 set $x$=1,$x$=2 是不合法的）。

print 语句计算表达式并将结果以逗号分隔形式输出，每次输出完毕需换行：

```
print 1,(2+3)
```

会产生以下输出：

```
1,5
```

## 输入格式

输入包含一个语法正确的程序。假设最多执行 100000 条 set 语句和 100000 条 print 语句。

## 输出格式

输出为执行给定程序所产生的结果。输入和输出文件的大小均不会超过 100KB。

 **本翻译由 AI 自动生成**

## 样例 #1

### 输入

```
When ($Mr. Bill$&lt;5)
   Set $mr._bill$=($mr.  bill$+1),$Y$=($Y$+10)
End When
When ($mr. Bill$&lt;10)
  Set $MR. BILL$=($mr. bill$+1)
  Print $mr. bill$,$Y$
End When
```

### 输出

```
3,20
6,40
7,40
8,40
9,40
10,40
```

