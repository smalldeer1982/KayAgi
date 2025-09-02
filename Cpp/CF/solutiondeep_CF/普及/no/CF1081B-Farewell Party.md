# 题目信息

# Farewell Party

## 题目描述

Chouti and his classmates are going to the university soon. To say goodbye to each other, the class has planned a big farewell party in which classmates, teachers and parents sang and danced.

Chouti remembered that $ n $ persons took part in that party. To make the party funnier, each person wore one hat among $ n $ kinds of weird hats numbered $ 1, 2, \ldots n $ . It is possible that several persons wore hats of the same kind. Some kinds of hats can remain unclaimed by anyone.

After the party, the $ i $ -th person said that there were $ a_i $ persons wearing a hat differing from his own.

It has been some days, so Chouti forgot all about others' hats, but he is curious about that. Let $ b_i $ be the number of hat type the $ i $ -th person was wearing, Chouti wants you to find any possible $ b_1, b_2, \ldots, b_n $ that doesn't contradict with any person's statement. Because some persons might have a poor memory, there could be no solution at all.

## 说明/提示

In the answer to the first example, all hats are the same, so every person will say that there were no persons wearing a hat different from kind $ 1 $ .

In the answer to the second example, the first and the second person wore the hat with type $ 1 $ and all other wore a hat of type $ 2 $ .

So the first two persons will say there were three persons with hats differing from their own. Similarly, three last persons will say there were two persons wearing a hat different from their own.

In the third example, it can be shown that no solution exists.

In the first and the second example, other possible configurations are possible.

## 样例 #1

### 输入

```
3
0 0 0
```

### 输出

```
Possible
1 1 1 ```

## 样例 #2

### 输入

```
5
3 3 2 2 2
```

### 输出

```
Possible
1 1 2 2 2 ```

## 样例 #3

### 输入

```
4
0 1 2 3
```

### 输出

```
Impossible
```

# AI分析结果

### 题目内容重写（中文）

**告别派对**

#### 题目描述

Chouti和他的同学们即将上大学。为了互相告别，班级计划举办一场盛大的告别派对，同学们、老师和家长们在派对上唱歌跳舞。

Chouti记得有$n$个人参加了派对。为了让派对更有趣，每个人都戴了一顶编号为$1, 2, \ldots, n$的奇怪帽子。可能有几个人戴了同一种帽子，有些种类的帽子可能没有人戴。

派对结束后，第$i$个人说，有$a_i$个人戴的帽子与他的不同。

已经过去了一些日子，Chouti忘记了其他人的帽子，但他对此感到好奇。设$b_i$为第$i$个人戴的帽子类型，Chouti希望你找到任何可能的$b_1, b_2, \ldots, b_n$，且不与任何人的陈述矛盾。由于有些人可能记忆不佳，可能根本不存在解决方案。

#### 说明/提示

在第一个样例的答案中，所有帽子都是相同的，所以每个人都会说没有人戴的帽子与类型$1$不同。

在第二个样例的答案中，第一个人和第二个人戴了类型$1$的帽子，其他人戴了类型$2$的帽子。

因此，前两个人会说有三个人戴的帽子与他们的不同。同样，最后三个人会说有两个人戴的帽子与他们的不同。

在第三个样例中，可以证明不存在解决方案。

在第一个和第二个样例中，可能存在其他可能的配置。

#### 样例 #1

##### 输入

```
3
0 0 0
```

##### 输出

```
Possible
1 1 1
```

#### 样例 #2

##### 输入

```
5
3 3 2 2 2
```

##### 输出

```
Possible
1 1 2 2 2
```

#### 样例 #3

##### 输入

```
4
0 1 2 3
```

##### 输出

```
Impossible
```

### 算法分类
**构造**

### 题解分析与结论

题目要求根据每个人所说的与自己帽子不同的人数，构造出一个可能的帽子分配方案。核心思路是将每个人所说的$a_i$转化为$n - a_i$，即与自己帽子相同的人数。然后根据这些人数进行分组，确保每组的人数与$n - a_i$一致，否则无解。

### 高星题解推荐

#### 1. 作者：Laolizi (赞：11)  
**星级：5**  
**关键亮点：**  
- 通过将$a_i$转化为$n - a_i$，简化问题。
- 使用排序和分组策略，确保每组人数与$n - a_i$一致。
- 代码简洁且高效，处理了无解情况。

**核心代码：**
```cpp
sort(a+1,a+n+1,cmp);
int m=1; 
while(m<=n){
    int cnt=0,now=m-1;
    while(a[m+cnt].value==a[m].value) ++cnt;
    if(cnt%a[m].value) puts("Impossible"),exit(0);
    for(int j=1; j<(cnt/a[m].value); ++j) {
        now+=a[m].value,++h;
        for(int k=1; k<=a[m].value; ++k) ans[a[now+k].num]=pot[h];
    }
    m+=cnt;
}
```

#### 2. 作者：lzyqwq (赞：3)  
**星级：4**  
**关键亮点：**  
- 使用容器存储相同$n - a_i$的人，确保每组人数一致。
- 通过分组策略，确保每组人数与$n - a_i$一致，否则无解。
- 代码清晰，逻辑严谨。

**核心代码：**
```cpp
for (int i = 1; i <= n; ++i) {
    if (mp[i].size() % i) return puts("Impossible"), 0;
    while (mp[i].size()) {
        ++cnt;
        for (int j = 1; j <= i; ++j) {
            ans[mp[i].back()] = cnt;
            mp[i].pop_back();
        }
    }
}
```

#### 3. 作者：Maysoul (赞：0)  
**星级：4**  
**关键亮点：**  
- 使用桶统计相同$n - a_i$的人，确保每组人数一致。
- 通过分组策略，确保每组人数与$n - a_i$一致，否则无解。
- 代码简洁，逻辑清晰。

**核心代码：**
```cpp
for (int i = 1; i <= n; ++i) {
    if(tot[i]%i!=0){
        cout<<"Impossible"<<endl;
        return 0;
    }
    int k=i,cnt=0;
    for (int j:id[i]){
        ans[j]=num;
        cnt++;
        if(cnt==k){
            cnt=0;
            num++;
        }
    }
}
```

### 最优关键思路或技巧
- **转化问题**：将$a_i$转化为$n - a_i$，简化问题。
- **分组策略**：根据$n - a_i$进行分组，确保每组人数与$n - a_i$一致，否则无解。
- **排序与分组**：通过排序和分组策略，确保每组人数与$n - a_i$一致。

### 可拓展之处
- 类似的问题可以通过分组和排序策略解决，如分配任务、资源分配等。
- 可以扩展到更复杂的帽子分配问题，如多种帽子类型、多种颜色等。

### 推荐题目
1. [P1081B - Farewell Party](https://www.luogu.com.cn/problem/CF1081B)
2. [P1081C - Farewell Party](https://www.luogu.com.cn/problem/CF1081C)
3. [P1081D - Farewell Party](https://www.luogu.com.cn/problem/CF1081D)

---
处理用时：45.27秒