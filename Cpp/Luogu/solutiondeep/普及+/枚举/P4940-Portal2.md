# 题目信息

# Portal2

## 题目背景

某地`ENLIGHTENED`的`XM`研究所正在研究`Portal`的处理法则，想要揭示`XM能量`的来源以及应用`XM能量`。`ENLIGHTENED`的首席科学家`Jacks`发现其能量的运算法则以及运算方法，但是方法十分复杂，仅靠人手工计算是很难算出答案的，所以它需要你协助他完成计算。

## 题目描述

`Portal`计算`XM能量`是通过个$2$个栈（$0$号栈，$1$号栈）实现的，它把对`XM`能量的操作如下

$PUSH$ $X$ $NUM$

把$NUM$加入到X号栈的栈顶。 

$POP$ $X$

把$X$号栈的栈顶元素**删除**。

$ADD$ $X$

**取出**$0$号栈和$1$号栈的元素各一个，并且把它的和放入$X$号栈。

$SUB$ $X$

**取出**$0$号栈和$1$号栈的元素各一个，并且把它的差的绝对值放入$X$号栈。
 
$DEL$ $X$

**清空**$X$号栈中所有元素不管栈是否为空。 

$MOVE$ $X$ $Y$ 

循环操直到$Y$号栈为空，把$Y$号栈的栈顶元素加入到$X$号栈，删除$Y$号栈的栈顶元素。 

**数据保证X和Y不相同**

$SWAP$

将两个栈的所有元素调换。

$END$

代表命令结束，并且分两行分别输出0号栈和1号栈由栈顶到栈底的元素的值，若栈内无元素，输出`NONE`。数据保证指令以`END`结束且仅有一个`END`，并且也需要输出`SUCCESS`。

~~$AKNOI$~~

~~等为无效操作，**无效操作后不接数字**。~~

**更正不会有类似无效操作**

对于每一行指令，若当前指令成功执行输出`SUCCESS`，若**取出**或**删除**元素时栈内为空或者没有对应指令输出`UNSUCCESS`并且不执行该行指令。

## 说明/提示

对于$20\%$的数据 数据保证不会出现`MOVE/SWAP`操作，$命令总数 \leq 100$

对于$40\%$的数据 $命令总数 \leq 1000$

对于$60\%$的数据 数据保证`MOVE/SWAP`的操作次数不会超过$10000$次，$命令总数 \leq 10^5$

对于$100\%$的数据 $0 \leq X,Y \leq 1,命令总数 \leq 10^6$ 

**数据保证无论任何情况，栈中元素的值$X$满足$0 \leq x \leq 2^{63}-1​$**

[题目创意来源OIERBBS](https://www.oierbbs.cn)

## 样例 #1

### 输入

```
PUSH 0 10
PUSH 0 20
PUSH 0 30
PUSH 0 40
PUSH 1 50
PUSH 1 60
ADD 0
ADD 0
ADD 0
END```

### 输出

```
SUCCESS
SUCCESS
SUCCESS
SUCCESS
SUCCESS
SUCCESS
SUCCESS
SUCCESS
UNSUCCESS
SUCCESS
150 30 20 10
NONE```

## 样例 #2

### 输入

```
PUSH 0 10
PUSH 0 20
PUSH 0 30
PUSH 0 40
PUSH 1 50
PUSH 1 60
MOVE 0 1
END```

### 输出

```
SUCCESS
SUCCESS
SUCCESS
SUCCESS
SUCCESS
SUCCESS
SUCCESS
SUCCESS
50 60 40 30 20 10
NONE```

# AI分析结果

### 综合分析与结论
这些题解均围绕模拟两个栈的多种操作展开，不同题解采用了不同的数据结构和算法来优化复杂度。7KByte 采用双端队列模拟栈并结合启发式合并；NewSjf 运用非旋 Treap 实现栈操作；leozhao123 使用多个 `std::list` 辅助实现；ganpig 用 `__gnu_cxx::rope` 逃课；cdx123456 采用双向链表实现。各题解在处理 `MOVE` 操作时复杂度和实现方式有所不同，整体复杂度大多控制在 $O(N log_2 N)$ 或更低。

### 所选题解
- **7KByte（5星）**
    - **关键亮点**：思路清晰，使用双端队列模拟栈，结合启发式合并优化 `MOVE` 操作复杂度，代码实现简洁明了，复杂度分析准确。
    - **个人心得**：题面提到无效操作但实际没有，导致多写了 100 行代码。
- **NewSjf（4星）**
    - **关键亮点**：采用非旋 Treap 实现栈操作，对 `MOVE` 操作的区间反转处理巧妙，复杂度分析合理。
    - **个人心得**：最初想用双端队列 $O(1)$ 合并但失败，后发现平衡树可以满足复杂度要求。

### 重点代码
#### 7KByte 双端队列 + 启发式合并
```cpp
deque<ll>q[2];
int f[2]={0,1};
int tag[2]={0,0};
// MOVE 操作
if(k[0]=='M'&&k[1]=='O'){
    scanf("%d%d",&x,&y);
    puts("SUCCESS");
    if(q[f[x]].size()<q[f[y]].size()){
        while(q[f[x]].size()){
            ll a;
            if(tag[f[x]])a=q[f[x]].front(),q[f[x]].pop_front();
            else a=q[f[x]].back(),q[f[x]].pop_back();
            if(tag[f[y]])q[f[y]].push_front(a);
            else q[f[y]].push_back(a);
        }
        tag[f[y]]^=1;
        swap(f[0],f[1]);
    }
    else{
        while(q[f[y]].size()){
            ll a;
            if(tag[f[y]])a=q[f[y]].front(),q[f[y]].pop_front();
            else a=q[f[y]].back(),q[f[y]].pop_back();
            if(tag[f[x]])q[f[x]].push_front(a);
            else q[f[x]].push_back(a);
        }
    }
}
```
**核心思想**：对于 `MOVE` 操作，根据两个栈的大小关系选择不同的合并策略，借助 `tag` 标记栈是否反转，通过双端队列的前后端操作模拟栈的进出。

#### NewSjf 非旋 Treap
```cpp
// MOVE 操作
void move(int x,int y) {
    int x1=0,x2=0,y1=0,y2=0;
    reverse(root[y],2,stk[y].end);
    split(root[x],x1,x2,1);
    split(root[y],y1,y2,1);
    merge(x2,x2,y2);
    merge(root[x],x1,x2);
    stk[x].end+=stk[y].end-1;
    stk[y].end=stk[y].begin;
}
```
**核心思想**：`MOVE` 操作通过区间反转和合并操作，将一个栈的元素合并到另一个栈中，利用非旋 Treap 的特性实现 $O(logN)$ 复杂度。

### 最优关键思路或技巧
- **数据结构选择**：不同数据结构各有优势，如双端队列模拟栈简单易实现，非旋 Treap 可高效处理区间操作。
- **启发式合并**：在处理 `MOVE` 操作时，通过比较栈的大小选择合适的合并方式，将复杂度从 $O(N^2)$ 优化到 $O(N log_2 N)$。
- **区间操作**：使用非旋 Treap 可以高效实现区间反转、合并等操作，将复杂操作的复杂度控制在 $O(logN)$。

### 可拓展之处
同类型题可能涉及更多栈或队列的操作，或者对操作复杂度有更高要求。类似算法套路包括使用不同的数据结构（如线段树、树状数组等）来优化操作复杂度，或者结合多种数据结构实现复杂操作。

### 推荐题目
- [P1160 队列安排](https://www.luogu.com.cn/problem/P1160)：考察链表的插入和删除操作。
- [P1449 后缀表达式](https://www.luogu.com.cn/problem/P1449)：考察栈的基本操作。
- [P3369 【模板】普通平衡树](https://www.luogu.com.cn/problem/P3369)：考察平衡树的基本操作。

---
处理用时：36.41秒