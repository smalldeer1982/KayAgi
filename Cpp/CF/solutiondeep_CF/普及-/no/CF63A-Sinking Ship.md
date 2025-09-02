# 题目信息

# Sinking Ship

## 题目描述

The ship crashed into a reef and is sinking. Now the entire crew must be evacuated. All $ n $ crew members have already lined up in a row (for convenience let's label them all from left to right with positive integers from 1 to $ n $ ) and await further instructions. However, one should evacuate the crew properly, in a strict order. Specifically:

The first crew members to leave the ship are rats. Then women and children (both groups have the same priority) leave the ship. After that all men are evacuated from the ship. The captain leaves the sinking ship last.

If we cannot determine exactly who should leave the ship first for any two members of the crew by the rules from the previous paragraph, then the one who stands to the left in the line leaves the ship first (or in other words, the one whose number in the line is less).

For each crew member we know his status as a crew member, and also his name. All crew members have different names. Determine the order in which to evacuate the crew.

## 样例 #1

### 输入

```
6
Jack captain
Alice woman
Charlie man
Teddy rat
Bob child
Julia woman
```

### 输出

```
Teddy
Alice
Bob
Julia
Charlie
Jack
```

# AI分析结果

【题目内容（中文重写）】
# 沉船

## 题目描述
船撞上了暗礁，正在下沉。现在全体船员必须撤离。所有 $n$ 名船员已经排成了一排（为方便起见，我们从左到右依次用从 1 到 $n$ 的正整数为他们编号），等待进一步指示。然而，必须以严格的顺序正确地撤离船员。具体如下：

首先离开船的是老鼠。然后是妇女和儿童（这两组优先级相同）离开船。之后所有男性撤离。船长最后离开正在下沉的船。

如果根据上述规则，对于任意两名船员，我们无法确切判断谁应该先离开船，那么排在队伍左边的人先离开船（换句话说，队伍中编号较小的人先离开）。

对于每名船员，我们知道他的船员身份以及他的名字。所有船员的名字都不同。请确定撤离船员的顺序。

## 样例 #1
### 输入
```
6
Jack captain
Alice woman
Charlie man
Teddy rat
Bob child
Julia woman
```

### 输出
```
Teddy
Alice
Bob
Julia
Charlie
Jack
```

【算法分类】
排序

【综合分析与结论】
这些题解的核心都是按照给定的优先级规则对船员进行排序并输出。各题解思路和方法有所不同：
- **Andysun06**：直接用字符串数组记录信息，通过四次遍历数组，按照老鼠、妇女和儿童、男人、船长的顺序输出符合条件的名字，未使用额外排序算法。
- **666DHG**：使用 `map` 预处理优先级，将信息存入结构体并利用优先队列自动排序，最后依次输出队列元素。
- **追风少年σχ**：将乘客类型转化为数字，用结构体记录乘客信息，自定义 `cmp` 函数，使用 `sort` 排序后输出。
- **chufuzhe**：用 `vector` 动态数组按优先性分组，最后依次输出每个组的名字。
- **Oscar12345**：用数组记录每个人的优先级，通过两层循环按照优先级顺序输出对应名字。
- **hensier**：用结构体记录乘客信息，标记等级，自定义 `cmp` 函数，使用 `sort` 排序后输出。

解决的难点在于如何根据给定的优先级规则对船员进行排序，不同题解采用了不同的数据结构和算法来实现这一目的。

【所选题解】
- **Andysun06（4星）**：
  - 关键亮点：思路简单直接，不使用复杂的数据结构和排序算法，通过多次遍历数组实现排序输出，代码易理解。
  - 个人心得：无。
- **666DHG（4星）**：
  - 关键亮点：使用优先队列自动排序，代码简洁，利用 `map` 预处理优先级，方便快捷。
  - 个人心得：提到本题简单，本地没测还一次过。
- **追风少年σχ（4星）**：
  - 关键亮点：将字符串类型转化为数字，使用结构体和自定义 `cmp` 函数，利用 `sort` 排序，逻辑清晰。
  - 个人心得：提到写得挺轻松，蒟蒻题解求过。

【重点代码】
- **Andysun06**：
```cpp
for(i=1;i<=n;++i){
    if(b[i]=="rat")
        cout<<a[i]<<endl;
}
for(i=1;i<=n;++i){
    if(b[i]=="woman"||b[i]=="child")
        cout<<a[i]<<endl;
}
for(i=1;i<=n;++i){
    if(b[i]=="man")
        cout<<a[i]<<endl;
}
for(i=1;i<=n;++i){
    if(b[i]=="captain")
        cout<<a[i]<<endl;
}
```
核心实现思想：通过四次遍历数组，分别判断每个船员的身份，按照优先级顺序输出名字。

- **666DHG**：
```cpp
map <string,int> M;
M["rat"]=1;
M["woman"]=M["child"]=2;
M["man"]=3;
M["captain"]=4;
priority_queue <Data> Q;
for (int i=1;i<=n;i++){
    cin>>name>>type;
    Q.push((Data){i,M[type],name});
}
while (!Q.empty()){
    cout<<Q.top().name<<"\n";
    Q.pop();
}
```
核心实现思想：用 `map` 预处理优先级，将信息存入结构体并加入优先队列，利用优先队列自动排序，最后依次输出队列元素。

- **追风少年σχ**：
```cpp
struct node{
    string name;
    int type,num;
};
bool cmp(node p,node q){
    if(p.type==q.type) return p.num<q.num;
    else return p.type<q.type;
}
int f(string s){
    if(s=="rat")return 0;
    if(s=="child"||s=="woman")return 1;
    if(s=="man")return 2;
    return 3;
}
sort(a+1,a+1+n,cmp);
```
核心实现思想：将乘客类型转化为数字，用结构体记录乘客信息，自定义 `cmp` 函数，使用 `sort` 排序。

【最优关键思路或技巧】
- 可以使用 `map` 来预处理优先级，方便后续比较和排序。
- 利用结构体存储乘客信息，自定义排序规则，使用 `sort` 或优先队列进行排序。

【拓展思路】
同类型题可能会有更多的优先级类别或更复杂的排序规则，类似算法套路可以是先确定优先级，再根据优先级对元素进行排序。可以使用不同的数据结构（如数组、结构体、优先队列等）和排序算法（如 `sort`、冒泡排序等）来实现。

【推荐洛谷题目】
1. P1177 【模板】快速排序
2. P1093 [NOIP2007 普及组] 奖学金
3. P1068 [NOIP2009 普及组] 分数线划定

---
处理用时：35.99秒