# 题目信息

# Suspects

## 题目描述

As Sherlock Holmes was investigating a crime, he identified $ n $ suspects. He knows for sure that exactly one of them committed the crime. To find out which one did it, the detective lines up the suspects and numbered them from $ 1 $ to $ n $ . After that, he asked each one: "Which one committed the crime?". Suspect number $ i $ answered either "The crime was committed by suspect number $ a_{i} $ ", or "Suspect number $ a_{i} $ didn't commit the crime". Also, the suspect could say so about himself ( $ a_{i}=i $ ).

Sherlock Holmes understood for sure that exactly $ m $ answers were the truth and all other answers were a lie. Now help him understand this: which suspect lied and which one told the truth?

## 说明/提示

The first sample has the single person and he confesses to the crime, and Sherlock Holmes knows that one person is telling the truth. That means that this person is telling the truth.

In the second sample there are three suspects and each one denies his guilt. Sherlock Holmes knows that only two of them are telling the truth. Any one of them can be the criminal, so we don't know for any of them, whether this person is telling the truth or not.

In the third sample the second and the fourth suspect defend the first and the third one. But only one is telling the truth, thus, the first or the third one is the criminal. Both of them can be criminals, so the second and the fourth one can either be lying or telling the truth. The first and the third one are lying for sure as they are blaming the second and the fourth one.

## 样例 #1

### 输入

```
1 1
+1
```

### 输出

```
Truth
```

## 样例 #2

### 输入

```
3 2
-1
-2
-3
```

### 输出

```
Not defined
Not defined
Not defined
```

## 样例 #3

### 输入

```
4 1
+2
-3
+4
-1
```

### 输出

```
Lie
Not defined
Lie
Not defined
```

# AI分析结果

### 题目内容
# 嫌疑人

## 题目描述
当夏洛克·福尔摩斯在调查一起犯罪案件时，他确定了$n$个嫌疑人。他确信其中恰好有一人犯下了罪行。为了找出是谁干的，这位侦探将嫌疑人排成一排，并从$1$到$n$给他们编号。之后，他问每个人：“是谁犯下了罪行？”嫌疑人$i$要么回答“是嫌疑人$a_{i}$犯下了罪行”，要么回答“嫌疑人$a_{i}$没有犯下罪行”。嫌疑人也可能这样说自己（$a_{i}=i$）。

夏洛克·福尔摩斯确切地知道恰好有$m$个回答是真话，而其他所有回答都是谎言。现在帮他弄清楚：哪个嫌疑人说了谎，哪个嫌疑人说了真话？

## 说明/提示
第一个样例中只有一个人，并且他承认了罪行，而夏洛克·福尔摩斯知道有一个人说的是真话。这意味着这个人说的是真话。

在第二个样例中有三个嫌疑人，每个人都否认自己有罪。夏洛克·福尔摩斯知道只有两个人说的是真话。他们中的任何一个都可能是罪犯，所以对于他们中的任何一个人，我们都不知道这个人说的是真话还是假话。

在第三个样例中，第二个和第四个嫌疑人维护第一个和第三个嫌疑人。但只有一个人说的是真话，因此，第一个或第三个是罪犯。他们两个都可能是罪犯，所以第二个和第四个嫌疑人可能说谎也可能说真话。第一个和第三个嫌疑人肯定在说谎，因为他们指责第二个和第四个嫌疑人。

## 样例 #1
### 输入
```
1 1
+1
```
### 输出
```
Truth
```

## 样例 #2
### 输入
```
3 2
-1
-2
-3
```
### 输出
```
Not defined
Not defined
Not defined
```

## 样例 #3
### 输入
```
4 1
+2
-3
+4
-1
```
### 输出
```
Lie
Not defined
Lie
Not defined
```

### 算法分类
枚举

### 综合分析与结论
这些题解的核心思路都是通过枚举每个嫌疑人是罪犯的情况，来判断每个人说的话的真假。具体要点如下：
 - **思路**：先假设所有人都不是罪犯，统计说真话的数量（通常是说其他人不是罪犯的人数）。然后依次假设每个嫌疑人是罪犯，根据当前假设调整真话数量，判断是否符合已知的$m$句真话。
 - **算法要点**：利用数组（桶）来记录说某个嫌疑人是罪犯或不是罪犯的人数，以便快速计算在不同假设下的真话数量。
 - **解决难点**：在于如何根据假设的罪犯和已知的真话数量准确判断每个人话语的真假，特别是在多种可能情况（如多个嫌疑人都有可能是罪犯）下的处理。

### 所选的题解
 - **作者：WYFwyf (赞：7)  星级：4星 关键亮点**：代码逻辑清晰，通过合理定义数组记录相关信息，逐步推导判断每个人话语的真假。
```cpp
#include<iostream>
#include<cstdio>
using namespace std;
int n,m,i,num[100100],yes[100100],no[100010],ans_no=0,ans_maybe=0,ans_is[100100];
int main()
{
    cin>>n>>m;
    for(i=1;i<=n;i++)
    {
        cin>>num[i];
        if(num[i]>0)
            yes[num[i]]++;    //说第i个人是罪犯的人数
        else
        {
            no[-num[i]]++; //说第i个人不是罪犯的人数
            ans_no++;      //说不是罪犯的总人数    
        }
    }
    for(i=1;i<=n;i++)
    {
        if(yes[i]+ans_no-no[i]==m)
        {
            ans_is[i]=1;
            ans_maybe++;   //可能是罪犯的人数
        }
    }   
    for(i=1;i<=n;i++)
    {
        if(num[i]>0)
        {
            if(ans_maybe==1&&ans_is[num[i]]==1)
                cout<<"Truth"<<endl;
            else if(ans_is[num[i]]==0)
                cout<<"Lie"<<endl;
            else
                cout<<"Not defined"<<endl;
        }
        else 
        {
            if(ans_is[-num[i]]==0)
                cout<<"Truth"<<endl;
            else if(ans_maybe==1)
                cout<<"Lie"<<endl;
            else
                cout<<"Not defined"<<endl;
        }
    }
    return 0;
}
```
 - **作者：OIerZhao_1025 (赞：5)  星级：4星 关键亮点**：与WYFwyf思路类似，代码简洁明了，变量命名有一定意义，便于理解。
```cpp
#include<bits/stdc++.h>//万能头
using namespace std;
const int maxn=1e5+10;//定值
int n,m,i,num[maxn],yes[maxn],no[maxn],ano,amb,ais[maxn];//全局变量
int main()
{
    cin>>n>>m;
    for(i=1;i<=n;i++)//依次设
    {
        cin>>num[i];
        if(num[i]>0)yes[num[i]]++; 
        else
        {
            no[-num[i]]++;
            ano++;       
        }
    }
    for(i=1;i<=n;i++)
        if(yes[i]+ano-no[i]==m)
        {
            ais[i]=1;
            amb++;   
        }
    for(i=1;i<=n;i++)
    {
        if(num[i]>0)//两种情况判断
        {
            if(amb==1&&ais[num[i]]==1) cout<<"Truth"<<endl;//三种情况判断
            else if(ais[num[i]]==0) cout<<"Lie"<<endl;
            else cout<<"Not defined"<<endl;
        }
        else 
        {
            if(ais[-num[i]]==0) cout<<"Truth"<<endl;//三种情况判断
            else if(amb==1) cout<<"Lie"<<endl;
            else cout<<"Not defined"<<endl;
        }
    }
    return 0;
}
```
 - **作者：rui_er (赞：4)  星级：4星 关键亮点**：思路清晰，对如何计算假设罪犯时真话数量的贡献阐述详细，代码实现简洁高效。
```cpp
//By: Luogu@rui_er(122461)
#include <bits/stdc++.h>
#define loop while(true)
#define rep(x,y,z) for(int x=y;x<=z;x++)
#define per(x,y,z) for(int x=y;x>=z;x--)
#define fil(x,y) memset(x, y, sizeof(x))
#define mulT0 int T; for(scanf("%d", &T);T;T--)
#define mulT1 int T, rnds; for(scanf("%d", &T),rnds=1;rnds<=T;rnds++)
using namespace std;
typedef long long ll;
const int N = 1e5+5;

int n, m, a[N], contribution[N], suspect[N], tot, s;

int main() {
    scanf("%d%d", &n, &m);
    rep(i, 1, n) {
        scanf("%d", &a[i]);
        if(a[i] > 0) ++contribution[a[i]];
        else --contribution[-a[i]], ++s;
    }
    rep(i, 1, n) if(s + contribution[i] == m) suspect[i] = 1, ++tot;
    rep(i, 1, n) {
        if(a[i] > 0) {
            if(!suspect[a[i]]) puts("Lie");
            else if(tot == 1) puts("Truth");
            else puts("Not defined");
        }
        else {
            if(!suspect[-a[i]]) puts("Truth");
            else if(tot == 1) puts("Lie");
            else puts("Not defined");
        }
    }
    return 0;
}
```

### 最优关键思路或技巧
利用桶这种数据结构记录说每个嫌疑人是或不是罪犯的人数，以空间换时间，将判断每个嫌疑人是否为罪犯的时间复杂度从$O(n^2)$优化到$O(n)$。同时，通过先假设所有人不是罪犯统计真话数量，再根据假设的罪犯调整该数量的方式，简化了判断逻辑。

### 可拓展思路
同类型题通常围绕逻辑推理展开，可能会增加嫌疑人数量、增加真话假话的判断条件等。类似算法套路是在面对逻辑判断类问题时，若直接暴力枚举复杂度高，可以考虑使用数据结构记录中间状态，优化计算过程。

### 洛谷推荐题目
 - [P1118 数字三角形](https://www.luogu.com.cn/problem/P1118)：涉及简单的路径枚举与状态推导。
 - [P1219 八皇后](https://www.luogu.com.cn/problem/P1219)：经典的搜索与枚举问题，锻炼逻辑判断和搜索能力。
 - [P1036 选数](https://www.luogu.com.cn/problem/P1036)：需要通过枚举组合来解决问题，与本题枚举思路类似。 

---
处理用时：104.87秒