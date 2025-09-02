# 题目信息

# Holidays

## 题目描述

School holidays come in Berland. The holidays are going to continue for $ n $ days. The students of school № $ N $ are having the time of their lives and the IT teacher Marina Sergeyevna, who has spent all the summer busy checking the BSE (Berland State Examination) results, has finally taken a vacation break! Some people are in charge of the daily watering of flowers in shifts according to the schedule. However when Marina Sergeyevna was making the schedule, she was so tired from work and so lost in dreams of the oncoming vacation that she perhaps made several mistakes. In fact, it is possible that according to the schedule, on some days during the holidays the flowers will not be watered or will be watered multiple times. Help Marina Sergeyevna to find a mistake.

## 说明/提示

Keep in mind that in the second sample the mistake occurs not only on the second day, but also on the sixth day, when nobody waters the flowers. However, you have to print the second day, i.e. the day with the minimal number.

## 样例 #1

### 输入

```
10 5
1 2
3 3
4 6
7 7
8 10
```

### 输出

```
OK
```

## 样例 #2

### 输入

```
10 5
1 2
2 3
4 5
7 8
9 10
```

### 输出

```
2 2
```

## 样例 #3

### 输入

```
10 5
1 2
3 3
5 7
7 7
7 10
```

### 输出

```
4 0
```

# AI分析结果

### 题目内容重写

**假期**

#### 题目描述

在Berland，学校假期即将到来，假期将持续$n$天。学校№$N$的学生们正享受着他们的时光，而IT老师Marina Sergeyevna在忙碌了整个夏天检查BSE（Berland国家考试）成绩后，终于迎来了她的假期！一些人按照轮班表负责每天浇花。然而，当Marina Sergeyevna制定轮班表时，她因为工作太累且沉浸在即将到来的假期梦想中，可能犯了一些错误。事实上，根据轮班表，在假期中的某些天，花可能没有被浇水，或者被浇了多次。请帮助Marina Sergeyevna找出错误。

#### 说明/提示

请注意，在第二个样例中，错误不仅发生在第二天，还发生在第六天，那天没有人浇花。然而，你需要输出第二天，即编号最小的那一天。

#### 样例 #1

##### 输入

```
10 5
1 2
3 3
4 6
7 7
8 10
```

##### 输出

```
OK
```

#### 样例 #2

##### 输入

```
10 5
1 2
2 3
4 5
7 8
9 10
```

##### 输出

```
2 2
```

#### 样例 #3

##### 输入

```
10 5
1 2
3 3
5 7
7 7
7 10
```

##### 输出

```
4 0
```

### 题解分析与结论

#### 题解对比

1. **模拟法**：多位作者（如songxiao、溪水瑶、Cream_等）采用了直接模拟的方法，通过数组记录每天浇水的次数，最后遍历数组检查是否每天都被浇水且不重复。这种方法简单直观，适合小规模数据，但时间复杂度较高。
  
2. **差分法**：ziiidan、曼恩薄荷、锦瑟华年等作者使用了差分法，通过标记区间起点和终点，最后通过前缀和恢复每天的浇水次数。这种方法在时间复杂度上更优，适合大规模数据。

3. **树状数组**：曼恩薄荷使用了树状数组来维护差分数组，进一步优化了查询和修改的效率。

4. **区间排序法**：rfsfreffr提出了区间排序的思路，通过排序后检查区间是否有重叠或空缺，这种方法在时间复杂度上也有优势，但实现较为复杂。

#### 最优关键思路

- **差分法**：通过标记区间起点和终点，最后通过前缀和恢复每天的浇水次数。这种方法在时间复杂度上更优，适合大规模数据。
  
- **树状数组**：结合差分法，使用树状数组进一步优化了查询和修改的效率。

#### 可拓展之处

- **区间覆盖问题**：类似的问题可以扩展到区间覆盖、区间查询等场景，使用差分法或树状数组可以有效解决。
  
- **大规模数据处理**：对于大规模数据，差分法和树状数组的优势更加明显，适合处理更复杂的问题。

#### 推荐题目

1. **P3372 【模板】线段树 1** - 考察线段树的基本操作，适合练习区间修改和查询。
  
2. **P3368 【模板】树状数组 2** - 考察树状数组的基本操作，适合练习区间修改和单点查询。
  
3. **P1908 逆序对** - 考察树状数组的应用，适合练习逆序对的计算。

### 精选题解

#### 题解1：ziiidan（差分法）

**星级：5星**

**关键亮点**：使用差分法，通过标记区间起点和终点，最后通过前缀和恢复每天的浇水次数。代码简洁高效，适合大规模数据。

**核心代码**：
```cpp
int main()
{
    n = read(); m = read();
    for(register int i = 1; i <= m; i++) 
    {
        fr = read(); to = read();
        c[fr]++;
        c[to + 1]--;
    }
    for(register int i = 1; i <= n; i++) 
    {
        c[i] = c[i - 1] + c[i];
        if(c[i] == 0) 
        {
            cout << i << ' ' << 0 << '\n';
            return 0;
        }
        if(c[i] > 1) 
        {
            cout << i << ' ' << c[i] << '\n';
            return 0;
        }
    }
    cout << "OK" << '\n';
    return 0;
}
```

#### 题解2：曼恩薄荷（树状数组）

**星级：4星**

**关键亮点**：结合差分法，使用树状数组进一步优化了查询和修改的效率。代码实现较为复杂，但效率更高。

**核心代码**：
```cpp
void add(int x,int v)
{
    while(x<=n)
    {
        tree[x] += v;
        x += lowbit(x);
    }
}

int sum(int x)
{
    int ret = 0;
    while(x != 0)
    {
        ret += tree[x];
        x -= lowbit(x);
    }
    return ret;
}

int main()
{
    scanf("%d%d",&n,&m);
    for(int i=1;i<=m;i++)
    {
        int l,r;
        scanf("%d%d",&l,&r);
        add(l,1);
        add(r+1,-1);
    }
    for(int i=1;i<=n;i++)
    {
        int s = sum(i);
        if(s != 1)
        {
            printf("%d %d",i,s);
            return 0;
        }
    }
    puts("OK");
    return 0;
}
```

#### 题解3：锦瑟华年（差分法）

**星级：4星**

**关键亮点**：使用差分法，代码简洁易懂，适合初学者理解差分的基本思想。

**核心代码**：
```cpp
int main(){
    int n,m,i;
    scanf("%d%d",&n,&m);
    for(i=1;i<=m;i++){
        int l,r;
        scanf("%d%d",&l,&r);
        a[l]+=1;a[r+1]-=1;
    }
    for(i=1;i<=n;i++){
        a[i]+=a[i-1];
        if(a[i]!=1){
            printf("%d %d",i,a[i]);
            return 0;
        }
    }
    printf("OK");
    return 0; 
}
```

---
处理用时：45.65秒