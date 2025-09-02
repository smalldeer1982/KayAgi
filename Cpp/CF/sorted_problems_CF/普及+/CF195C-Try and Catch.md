---
title: "Try and Catch"
layout: "post"
diff: 普及+/提高
pid: CF195C
tag: []
---

# Try and Catch

## 题目描述

Vasya 正在开发他的编程语言 VPL（Vasya 编程语言），目前他在实现异常处理系统。他认为异常处理的机制应该如下运作：

异常由 try-catch 块来处理。有两个操作符与异常块相关：

1. **try 操作符**：用于开启一个新的 try-catch 块。
2. **catch(<exception_type>, <message>) 操作符**：用于关闭最后一个尚未关闭的 try-catch 块。这个块仅在捕获到类型为 <exception_type> 的异常时被激活。当块被激活时，屏幕将显示 <message>。如果没有打开的 try-catch 块，则无法使用 catch 操作符。

异常仅在使用 throw 操作符时才会抛出。throw(<exception_type>) 操作符会创建指定类型的异常。

假如由于某个 throw 操作符，程序抛出了类型为 $a$ 的异常。那么将激活一个 try-catch 块，该块的 try 操作符在程序中位于该 throw 操作符之前，并且该块的 catch 操作符使用了异常类型 $a$，且它的位置在 throw 之后。如果存在多个这样的 try-catch 块，系统将激活 catch 操作符位置最靠前的块。如果没有满足条件的 try-catch 块被激活，屏幕将显示 "Unhandled Exception"。

为测试该系统，Vasya 编写了一个程序，其中只包含 try、catch 和 throw 操作符，并且每行最多包含一个操作符。程序中恰好有一个 throw 操作符。

你的任务是：根据给定的 VPL 语言程序，确定程序执行后屏幕将显示的消息。

## 输入格式

第一行是一个整数 $n$ $ (1 \le n \le 10^5)$，表示程序的行数。接下来的 $n$ 行是用 VPL 语言编写的程序代码。每行可以最多包含一个操作符，这意味着输入文件中可能有空行或只有空格的行。

程序中只出现 try、catch 和 throw 操作符。保证程序的语法正确，每个开启的 try-catch 块都有关闭，且 catch 操作符的使用是基于存在开启的 try-catch 块。程序中有且只有一个 throw 操作符。每行的开头、结尾以及括号、逗号或引号的两侧可能有多余的空格。

异常的类型由一个非空字符串表示，仅由英文字母组成，长度不超过 20 个字符。消息内容是一个非空字符串，由英文字母、数字和空格组成，被引号包围。最终输出时不打印引号。消息的长度不超过 20 个字符。

输入文件中任何一行的长度不会超过 50 个字符。

## 输出格式

输出程序执行后屏幕上显示的消息。

## 说明/提示

在第一个例子中，有两个符合条件的 try-catch 块：try-catch(BE, "BE in line 3") 和 try-catch(AE, "AE somewhere")。异常类型是 AE，因此第二个块将被激活，因为其 catch 操作符的参数与异常类型匹配。

在第二个例子中，try-catch(AE, "AE in line 3") 和 try-catch(AE, "AE somewhere") 都符合条件，但第一个块的 catch 操作符位置较早，因此第一个块将被激活。

在第三个例子中，没有可被类型为 CE 的异常激活的块。

 **本翻译由 AI 自动生成**

## 样例 #1

### 输入

```
8
try
    try
        throw ( AE ) 
    catch ( BE, &quot;BE in line 3&quot;)

    try
    catch(AE, &quot;AE in line 5&quot;) 
catch(AE,&quot;AE somewhere&quot;)

```

### 输出

```
AE somewhere

```

## 样例 #2

### 输入

```
8
try
    try
        throw ( AE ) 
    catch ( AE, &quot;AE in line 3&quot;)

    try
    catch(BE, &quot;BE in line 5&quot;) 
catch(AE,&quot;AE somewhere&quot;)

```

### 输出

```
AE in line 3

```

## 样例 #3

### 输入

```
8
try
    try
        throw ( CE ) 
    catch ( BE, &quot;BE in line 3&quot;)

    try
    catch(AE, &quot;AE in line 5&quot;) 
catch(AE,&quot;AE somewhere&quot;)

```

### 输出

```
Unhandled Exception

```

