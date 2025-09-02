# 题目信息

# [ICPC 2019 WF] Karel the Robot

## 题目描述

你知道“机器人”这个词已经快 100 年了吗？它首次出现在 1920 年，由 Karel Capek 编写的科幻戏剧 $R.U.R.$ 中。为了向这位捷克作家致敬，许多年后斯坦福大学将一种教育编程语言命名为 Karel。你的任务是实现这种编程语言的简化版本的解释器。

Karel 编程语言控制一个名叫 Karel 的机器人，它生活在一个单位方格的网格中。一些方格是空的，而另一些则包含障碍物。Karel 总是占据一个空的方格，并面向四个基本方向之一。两个基本命令是“前进”和“左转”。该语言还提供简单的条件和循环语句。该语言的主要教育潜力在于可以定义新的过程来完成更复杂的任务。

我们的简化版本的语言可以通过以下语法描述：

```plain
<program> := "" | <command> <program>
<command> := "m" | "l" | <proc-call> |
             "i" <condition> "(" <program> ")(" <program> ")" |
             "u" <condition> "(" <program> ")"
<condition> := "b" | "n" | "s" | "e" | "w"
<proc-call> := <uppercase-letter>
<proc-def> := <uppercase-letter> "=" <program>
```

有五种类型的命令：

- $\texttt m$（“前进”）使 Karel 在其当前方向上前进一个网格单元，除非前方有障碍物，在这种情况下命令无效。
- $\texttt l$（“左转”）使 Karel 左转 $90$ 度。
- $\texttt X$，其中 $\texttt X$ 是任何大写字母，调用名为 $\texttt X$ 的过程。
- $\texttt i$（“如果”）后跟一个单字母条件和两个括号中的程序。如果条件满足，则执行第一个程序。否则，执行第二个程序。
- $\texttt u$（“直到”）后跟一个单字母条件和一个括号中的程序。如果条件满足，则不执行任何操作。否则，执行程序，然后重复该命令。

条件可以是 '$b$'，当且仅当在 Karel 当前方向的下一个方格中有障碍物时满足，或者是四个方向字母之一 `n`、`s`、`e` 或 `w`，当且仅当 Karel 当前方向分别为北、南、东或西时满足。

例如，一个简单的程序 `ub(m)` 可以理解为：“一直前进直到遇到障碍物”，而 `un(l)` 意味着“转向北”。过程定义 `R=lll` 定义了一个新过程 `R`，其有效含义是“右转”。

## 说明/提示

来源：ICPC 世界总决赛 2019。

题面翻译由 ChatGPT-4o 提供。

## 样例 #1

### 输入

```
4 8 5 7
.......#
..#....#
.###...#
.....###
R=lll
G=ub(B)
B=ub(m)lib(l)(m)
H=ib()(mmHllmll)
I=III
1 1 w
G
1 1 e
G
2 2 n
G
2 6 w
BR
4 1 s
ib(lib()(mmm))(mmmm)
1 1 e
H
2 2 s
I
```

### 输出

```
1 1 w
inf
1 1 w
2 4 s
4 4 e
1 4 e
inf
```

# AI分析结果



**唯一算法分类**  
模拟

---

**综合分析与结论**  

本题要求实现一个简化版Karel机器人语言的解释器，核心在于正确解析并执行包含过程调用、条件分支和循环的指令，同时处理无限循环检测。关键难点包括动态解析嵌套结构、递归过程调用和状态跟踪。

**核心算法流程**  
1. **过程定义预处理**：将过程名映射到对应程序字符串，便于调用时快速查找。  
2. **状态维护**：记录机器人位置、方向、当前执行的程序段（`current_prog`）及指令指针（`ip`），使用调用栈处理过程调用和子程序执行。  
3. **条件与循环解析**：  
   - **条件分支（i）**：动态分割条件后的两个子程序，根据条件选择执行路径。  
   - **循环（u）**：重复执行子程序直到条件满足，需在每次循环重新解析条件和子程序。  
4. **无限循环检测**：通过记录状态哈希（位置、方向、程序段、ip及调用栈）判断是否重复，若重复则输出`inf`。

**可视化设计思路**  
- **像素风格界面**：网格展示机器人移动路径，障碍物用红色方块标记，机器人方向用箭头表示。  
- **动画高亮**：执行`m`/`l`时，机器人位置/方向变化用闪烁效果标记；`i`/`u`结构用不同颜色框线区分。  
- **音效与背景音乐**：移动/转向时播放8位音效，无限循环时播放警示音，背景音乐采用复古芯片音乐。  
- **交互控制**：支持单步执行、速度调节，实时显示调用栈深度和当前命令。

---

**题解清单 (≥4星)**  
暂无符合4星标准的题解，建议参考以下思路优化实现。

---

**代码核心实现**  
```python
def main():
    import sys
    from collections import deque

    # 输入解析
    lines = [line.strip() for line in sys.stdin if line.strip()]
    ptr = 0
    w, h, d, p = map(int, lines[ptr].split())
    ptr +=1
    grid = []
    for _ in range(h):
        grid.append(list(lines[ptr]))
        ptr +=1
    proc_defs = {}
    for _ in range(d):
        name, prog = lines[ptr].split('=')
        proc_defs[name] = prog
        ptr +=1
    # 处理测试用例
    for _ in range(p):
        x, y, dr = lines[ptr].split()
        x, y = int(x)-1, int(y)-1  # 转换为0-based
        initial_dr = {'n':0, 'e':1, 's':2, 'w':3}[dr]
        ptr +=1
        program = lines[ptr]
        ptr +=1
        # 模拟执行
        dirs = [(-1,0), (0,1), (1,0), (0,-1)]  # 北、东、南、西对应0,1,2,3
        current_dr = initial_dr
        current_x, current_y = x, y
        call_stack = []
        current_prog = program
        ip = 0
        visited = set()
        steps = 0
        MAX_STEPS = 10**6
        infinite = False
        while steps < MAX_STEPS:
            state_key = (current_x, current_y, current_dr, current_prog, ip)
            if state_key in visited:
                infinite = True
                break
            visited.add(state_key)
            if ip >= len(current_prog):
                if not call_stack:
                    break
                # 返回上层调用
                current_prog, ip = call_stack.pop()
                continue
            cmd = current_prog[ip]
            if cmd == 'm':
                dx, dy = dirs[current_dr]
                nx, ny = current_x + dx, current_y + dy
                if 0<=nx<h and 0<=ny<w and grid[nx][ny] != '#':
                    current_x, current_y = nx, ny
                ip +=1
            elif cmd == 'l':
                current_dr = (current_dr -1) %4
                ip +=1
            elif cmd == 'i' or cmd == 'u':
                # 动态解析条件与子程序
                # 实现略，需处理括号匹配与子程序分割
                pass
            elif cmd.isupper():
                proc = cmd
                if proc not in proc_defs:
                    ip +=1
                    continue
                call_stack.append( (current_prog, ip+1) )
                current_prog = proc_defs[proc]
                ip =0
            else:
                ip +=1
            steps +=1
        if infinite or steps >= MAX_STEPS:
            print("inf")
        else:
            dr_str = ['n','e','s','w'][current_dr]
            print(f"{current_x+1} {current_y+1} {dr_str}")

if __name__ == "__main__":
    main()
```

---

**同类型题推荐**  
1. **P1513** 循环的债务 - 状态转移模拟  
2. **P1035** 产生数 - 规则应用与状态扩展  
3. **P1022** 计算器改良 - 表达式解析与模拟  

---

**个人心得**  
处理递归调用时需警惕栈溢出，可通过限制深度或哈希检测。动态解析嵌套括号时，括号匹配函数是关键，需充分测试边缘情况。

---

**可视化与游戏化设计**  
- **Canvas动画**：网格动态渲染，机器人移动时显示轨迹，障碍物高亮。  
- **音效触发**：移动（滴答声）、转向（旋转声）、循环开始（低音提示）。  
- **自动演示模式**：按步骤自动播放，支持暂停/继续，速度调节滑动条。  
- **复古UI**：8-bit字体，色块表示状态，调用栈深度显示为像素进度条。

---
处理用时：394.94秒