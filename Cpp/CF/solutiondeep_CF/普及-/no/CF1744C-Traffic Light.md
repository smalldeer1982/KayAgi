# 题目信息

# Traffic Light

## 题目描述

You find yourself on an unusual crossroad with a weird traffic light. That traffic light has three possible colors: red (r), yellow (y), green (g). It is known that the traffic light repeats its colors every $ n $ seconds and at the $ i $ -th second the color $ s_i $ is on.

That way, the order of the colors is described by a string. For example, if $ s= $ "rggry", then the traffic light works as the following: red-green-green-red-yellow-red-green-green-red-yellow- ... and so on.

More formally, you are given a string $ s_1, s_2, \ldots, s_n $ of length $ n $ . At the first second the color $ s_1 $ is on, at the second — $ s_2 $ , ..., at the $ n $ -th second the color $ s_n $ is on, at the $ n + 1 $ -st second the color $ s_1 $ is on and so on.

You need to cross the road and that can only be done when the green color is on.

You know which color is on the traffic light at the moment, but you don't know the current moment of time. You need to find the minimum amount of time in which you are guaranteed to cross the road.

You can assume that you cross the road immediately.

For example, with $ s= $ "rggry" and the current color r there are two options: either the green color will be on after $ 1 $ second, or after $ 3 $ . That way, the answer is equal to $ 3 $ — that is the number of seconds that we are guaranteed to cross the road, if the current color is r.

## 说明/提示

The first test case is explained in the statement.

In the second test case the green color is on so you can cross the road immediately.

In the third test case, if the red color was on at the second second, then we would wait for the green color for one second, and if the red light was on at the first second, then we would wait for the green light for two seconds.

In the fourth test case the longest we would wait for the green color is if we wait for it starting from the fifth second.

## 样例 #1

### 输入

```
6
5 r
rggry
1 g
g
3 r
rrg
5 y
yrrgy
7 r
rgrgyrg
9 y
rrrgyyygy```

### 输出

```
3
0
2
4
1
4```

# AI分析结果

### 题目内容
# 交通信号灯

## 题目描述
你站在一个不寻常的十字路口，这里有一个奇怪的交通信号灯。这个信号灯有三种可能的颜色：红（r）、黄（y）、绿（g）。已知信号灯每 $n$ 秒重复一次颜色序列，在第 $i$ 秒显示颜色 $s_i$。

也就是说，颜色的顺序由一个字符串描述。例如，如果 $s =$ "rggry"，那么信号灯的工作模式如下：红 - 绿 - 绿 - 红 - 黄 - 红 - 绿 - 绿 - 红 - 黄 -... 依此类推。

更正式地说，给定一个长度为 $n$ 的字符串 $s_1, s_2, \ldots, s_n$。在第一秒显示颜色 $s_1$，在第二秒显示 $s_2$，...，在第 $n$ 秒显示颜色 $s_n$，在第 $n + 1$ 秒又显示颜色 $s_1$，依此类推。

你需要过马路，而只有当绿灯亮起时才能过马路。

你知道此刻信号灯显示的颜色，但不知道当前具体是第几秒。你需要找出在保证能过马路的情况下，最少需要等待的时间。

假设你能在绿灯亮起时立即过马路。

例如，对于 $s =$ "rggry" 且当前颜色为 r 的情况，有两种可能：要么绿灯在 1 秒后亮起，要么在 3 秒后亮起。所以，答案是 3，即如果当前颜色为 r，我们保证能过马路所需等待的秒数。

## 说明/提示
第一个测试用例在题目描述中有解释。

在第二个测试用例中，绿灯亮着，所以你可以立即过马路。

在第三个测试用例中，如果红灯在第二秒亮起，那么我们需要等待 1 秒绿灯亮起；如果红灯在第一秒亮起，那么我们需要等待 2 秒绿灯亮起。

在第四个测试用例中，如果我们从第五秒开始等待绿灯，等待时间是最长的。

## 样例 #1
### 输入
```
6
5 r
rggry
1 g
g
3 r
rrg
5 y
yrrgy
7 r
rgrgyrg
9 y
rrrgyyygy
```
### 输出
```
3
0
2
4
1
4
```

### 算法分类
字符串

### 综合分析与结论
这些题解的核心思路都是围绕如何处理循环字符串，找到给定字符到最近绿灯字符 'g' 的最大距离。大部分题解采用了破环为链的方法，即将原字符串复制一份接在原字符串后面，这样就可以在一个线性的字符串中处理循环相关问题。不同题解在具体实现上有所差异，例如有的使用队列模拟，有的利用数组记录位置并结合二分查找，有的通过从后往前循环记录每个位置往后第一个 'g' 的位置等。

### 所选的题解
- **作者：沉石鱼惊旋（4星）**
  - **关键亮点**：使用 `queue` 模拟题意，通过循环两次处理可能跨循环节的情况，时间复杂度为 $\mathcal O(n)$。
  - **重点代码**：
```cpp
void solve()
{
    ans=INT_MIN;
    while(!q.empty())
    {
        q.pop();
    }
    scanf("%d %c%s",&n,&tmp,c+1);
    for(int i=1;i<=n+n;i++)
    {
        z=i;
        if(z>n)
        {
            z-=n;
        }
        if(i<=n&&c[z]==tmp)
        {
            q.push(z);
        }
        if(c[z]=='g'&&!q.empty())//找到g并且有当前字符
        {
            ans=max(ans,i-q.front());//取一个最大的时间差
            while(!q.empty())
            {
                q.pop();
            }
        }
    }
    printf("%d\n",ans);
}
```
  - **核心实现思想**：遍历长度为 $2n$ 的字符串，当遇到当前字符时将其位置入队，遇到 'g' 且队列不为空时，计算当前位置与队首元素（最早出现的当前字符位置）的差值，并更新最大差值，然后清空队列。

- **作者：Allanljx（4星）**
  - **关键亮点**：破环为列后，从后往前循环记录从每个位置往后（包括该位置）第一个 'g' 出现的位置，最后通过遍历原字符串计算并取最大距离。
  - **重点代码**：
```cpp
for(int i=2*l;i>=1;i--)
{
    if(a[i]=='g') qz[i]=i;
    else qz[i]=qz[i+1];
}
int maxn=0;
for(int i=1;i<=l;i++)
{
    if(a[i]!=ch) continue;
    maxn=max(maxn,qz[i]-i);
}
```
  - **核心实现思想**：首先从后往前遍历复制后的字符串，记录每个位置往后第一个 'g' 的位置。然后遍历原字符串，对于每个与给定字符相同的位置，计算其与记录的 'g' 位置的差值，取最大值。

- **作者：zajasi（4星）**
  - **关键亮点**：思路清晰，先按序记录原字符串及复制后的字符串中所有 'g' 的位置，然后对每个目标字符通过二分查找找到离它最近的 'g'，计算并更新最大距离。
  - **重点代码**：
```cpp
vector<int> v;
for(int i=1;i<a.size();i++){
    if(a[i]=='g')v.push_back(i);
}
for(int i=1;i<a.size();i++){
    if(a[i]=='g')v.push_back(i+n);
}
int z=LLONG_MIN;
for(int i=1;i<a.size();i++){
    if(a[i]==c){
        int l=lower_bound(v.begin(),v.end(),i)-v.begin();
        z=max(z,v[l]-i);
    }
}
```
  - **核心实现思想**：将原字符串和复制后的字符串中 'g' 的位置存入向量 `v` 中，遍历原字符串，对于每个给定字符，使用 `lower_bound` 找到 `v` 中离它最近的 'g' 的位置，计算距离并更新最大距离。

### 最优关键思路或技巧
破环为链的方法是解决此类循环字符串问题的关键技巧，通过将原字符串复制一份接在后面，将循环问题转化为线性问题，便于后续处理。同时，利用合适的数据结构（如队列、数组等）记录位置信息，并结合相应的算法（如二分查找）来高效地找到最近的目标字符，从而解决问题。

### 可拓展之处
同类型题通常围绕循环字符串的特定字符查找、距离计算等展开。类似的算法套路包括处理循环结构时破环为链的思想，以及利用数据结构辅助记录和查找信息。例如，对于一些需要在循环序列中查找特定元素的问题，都可以考虑这种方法。

### 洛谷推荐题目
- [P1308 统计单词数](https://www.luogu.com.cn/problem/P1308)：涉及字符串查找与统计，与本题处理字符串的字符查找有相似之处。
- [P1593 因子和阶乘](https://www.luogu.com.cn/problem/P1593)：虽然涉及数学运算，但在处理字符串形式的输入以及根据特定规则处理字符方面与本题有一定关联。
- [P2219 数的分解](https://www.luogu.com.cn/problem/P2219)：在对字符串形式的数据进行处理和分析上，与本题有类似的思维方式。 

---
处理用时：65.11秒