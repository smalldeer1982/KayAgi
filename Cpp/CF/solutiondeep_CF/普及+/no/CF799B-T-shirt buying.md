# 题目信息

# T-shirt buying

## 题目描述

A new pack of $ n $ t-shirts came to a shop. Each of the t-shirts is characterized by three integers $ p_{i} $ , $ a_{i} $ and $ b_{i} $ , where $ p_{i} $ is the price of the $ i $ -th t-shirt, $ a_{i} $ is front color of the $ i $ -th t-shirt and $ b_{i} $ is back color of the $ i $ -th t-shirt. All values $ p_{i} $ are distinct, and values $ a_{i} $ and $ b_{i} $ are integers from $ 1 $ to $ 3 $ .

 $ m $ buyers will come to the shop. Each of them wants to buy exactly one t-shirt. For the $ j $ -th buyer we know his favorite color $ c_{j} $ .

A buyer agrees to buy a t-shirt, if at least one side (front or back) is painted in his favorite color. Among all t-shirts that have colors acceptable to this buyer he will choose the cheapest one. If there are no such t-shirts, the buyer won't buy anything. Assume that the buyers come one by one, and each buyer is served only after the previous one is served.

You are to compute the prices each buyer will pay for t-shirts.

## 样例 #1

### 输入

```
5
300 200 400 500 911
1 2 1 2 3
2 1 3 2 1
6
2 3 1 2 1 1
```

### 输出

```
200 400 300 500 911 -1 
```

## 样例 #2

### 输入

```
2
1000000000 1
1 1
1 2
2
2 1
```

### 输出

```
1 1000000000 
```

# AI分析结果

### 题目内容
# T恤购买

## 题目描述
一批共$n$件T恤到货。每件T恤由三个整数$p_{i}$、$a_{i}$和$b_{i}$描述，其中$p_{i}$是第$i$件T恤的价格，$a_{i}$是第$i$件T恤的正面颜色，$b_{i}$是第$i$件T恤的背面颜色。所有$p_{i}$的值都不同，$a_{i}$和$b_{i}$的值是介于$1$到$3$之间的整数。

将会有$m$位顾客来到商店。他们每个人都只想买一件T恤。对于第$j$位顾客，我们知道他最喜欢的颜色$c_{j}$。

如果一件T恤至少有一面（正面或背面）是顾客喜欢的颜色，那么这位顾客就会同意购买这件T恤。在所有颜色可接受的T恤中，他会选择最便宜的那件。如果没有这样的T恤，这位顾客就不会购买任何东西。假设顾客们一个接一个地来，并且只有在前一位顾客服务完之后，下一位顾客才会得到服务。

你需要计算出每位顾客购买T恤所支付的价格。

## 样例 #1
### 输入
```
5
300 200 400 500 911
1 2 1 2 3
2 1 3 2 1
6
2 3 1 2 1 1
```
### 输出
```
200 400 300 500 911 -1 
```

## 样例 #2
### 输入
```
2
1000000000 1
1 1
1 2
2
2 1
```
### 输出
```
1 1000000000 
```

### 算法分类
模拟

### 综合分析与结论
这道题主要考查对顾客购买T恤逻辑的模拟实现。各题解思路主要围绕如何高效存储和查找符合顾客颜色喜好且价格最低的T恤。算法要点在于根据颜色对T恤进行分类存储，难点是处理已被购买的T恤，避免重复选择。不同题解采用了优先队列、排序数组、单调指针、桶排序等不同方式来解决问题。

### 所选的题解
- **作者：爬行者小郑 (5星)**
  - **关键亮点**：使用优先队列存储不同颜色的T恤，通过结构体记录T恤的编号、价格和颜色，利用重载运算符实现小顶堆，逻辑清晰，代码简洁明了。同时注意到正反面颜色相同的衣服在优先队列中避免重复放入。
  - **重点代码**：
```cpp
struct Node//衣服
{
    int id,v,col1,col2;//编号，价钱，两个颜色
    bool operator < (const Node &a)const//重载运算符
    {
        return v>a.v;//优先队列默认是大顶堆，所以小于号要变成大于号
    }
}t[MAXN];
priority_queue<Node>q1;
priority_queue<Node>q2;
priority_queue<Node>q3;
//...
for(int i=1;i<=n;i++)
{
    t[i].id=i;/记录编号
    bool v1=0,v2=0,v3=0;//防止正反面一样被放两次
    if(t[i].col1==1)q1.push(t[i]),v1=1;
    if(t[i].col2==1&&v1==0)q1.push(t[i]);//放过就不要再放了
    if(t[i].col1==2)q2.push(t[i]),v2=1;
    if(t[i].col2==2&&v2==0)q2.push(t[i]);
    if(t[i].col1==3)q3.push(t[i]),v3=1;
    if(t[i].col2==3&&v3==0)q3.push(t[i]);
}
//...
for(int i=1;i<=m;i++)
{
    int x;
    cin>>x;//要买什么颜色
    if(x==1)
    {
        bool flag=0;//看一眼是否可以买到
        while(!q1.empty())
        {
            Node tmp=q1.top();//取出来堆顶
            if(vis[tmp.id])q1.pop();//如果买过就pop掉
            else
            {
                cout<<tmp.v<<" ";flag=1;//成功买到，记录flag
                vis[tmp.id]=1;//记录买过了
                q1.pop();//pop掉
                break;//递前退出while(!q1.empty())的循环
            }
        }
        if(!flag)//没买成
        cout<<-1<<" ";//输出-1（买不到）
    }
    //...
}
```
  - **核心实现思想**：先将T恤按颜色分别放入对应的优先队列，购买时从相应颜色的优先队列中取出价格最低且未被购买过的T恤，若队列为空则输出 -1。

- **作者：AuroraIris (4星)**
  - **关键亮点**：通过三个排序数组分别存储不同颜色的T恤价格及对应在原数组中的位置，用一个布尔数组记录T恤是否被选择，利用指针遍历数组来模拟购买过程，思路直观。
  - **重点代码**：
```pascal
procedure sort1(l,r: longint);
var
    i,j,x,y: longint;
begin
    i:=l;
    j:=r;
    x:=b[(l+r) div 2];
    repeat
        while b[i]<x do
            inc(i);
        while x<b[j] do
            dec(j);
        if not(i>j) then
        begin
            y:=b[i];
            b[i]:=b[j];
            b[j]:=y;
            y:=b1[i];
            b1[i]:=b1[j];
            b1[j]:=y;
            inc(i);
            j:=j-1;
        end;
    until i>j;
    if l<j then
        sort1(l,j);
    if i<r then
        sort1(i,r);
end;
//...
for i:=1 to n do
    if (cx[i]=1) or (cy[i]=1) then
    begin
        inc(p1);
        b[p1]:=a[i];
        b1[p1]:=i;//当前这件衣服在原数组中的位置
    end;
//...
sort1(1,p1);
//...
for i:=1 to m do
    begin
        if num[i]=1 then
        begin
            while pd[b1[h1]] do inc(h1);//这件衣服如果被选了，那么往下找第一件没有选择的
            if h1>p1 then begin write(-1,' '); continue; end;//如果没衣服了，输出-1
            write(b[h1],' ');
            pd[b1[h1]]:=true;//这件衣服选了
            inc(h1);//到下一件衣服
        end;
        //...
    end;
```
  - **核心实现思想**：先将符合各颜色要求的T恤价格及位置存入对应数组并排序，购买时通过移动指针找到未被购买且价格最低的T恤，若指针越界则输出 -1。

### 最优关键思路或技巧
使用优先队列能高效地维护每个颜色的T恤集合，并快速获取价格最低的T恤，同时通过记录T恤的编号和使用布尔数组标记已购买的T恤，可以有效避免重复选择。这种数据结构与标记结合的方式，简洁且高效地模拟了顾客购买T恤的过程。

### 可拓展之处
此类题目属于模拟实际场景中选择决策的问题，类似套路还可见于根据不同条件选择资源、任务分配等场景。拓展时可增加颜色种类、增加T恤属性、改变顾客选择策略等，以增加题目的复杂度。

### 洛谷相似题目推荐
- [P1031 均分纸牌](https://www.luogu.com.cn/problem/P1031)
- [P1223 排队接水](https://www.luogu.com.cn/problem/P1223)
- [P1908 逆序对](https://www.luogu.com.cn/problem/P1908)

### 个人心得摘录与总结
爬行者小郑提到要注意正反面颜色相同的衣服，在一个优先队列里面不要放两次，这是避免重复计算、提高效率的关键细节，提醒在处理数据存储时要充分考虑数据的特性，避免冗余。 

---
处理用时：68.54秒