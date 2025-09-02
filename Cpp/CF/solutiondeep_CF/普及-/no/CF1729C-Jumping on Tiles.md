# 题目信息

# Jumping on Tiles

## 题目描述

### 题目大意

给定一个字符串 $s$，polycarp 欲从字符串首跳到字符串末 ($s_1$ → $s_n$，其中 $n$ 表示该字符串长度)。

假设 polycarp 现从 $a_i$ 跳到了 $a_j$ 我们定义这一次跳跃的权值为 $|\operatorname{index}(a_i) - \operatorname{index}(a_j)|$，其中 $\operatorname{index}$
 表示该字符在字母表中的序号 ( 如 $\operatorname{index}('a') = 1, \; \operatorname{index}('z') = 26$ )。
 
 请构造出一种在保证**权值和最小**的情况下**经过的字符最多**的跳跃方案 ( 当然，同一个字符只能经过一次，其中同一个仅指在字符串中的位置相同 )。

## 样例 #1

### 输入

```
6
logic
codeforces
bca
aaaaaaaaaaa
adbaadabad
to```

### 输出

```
9 4
1 4 3 5
16 10
1 8 3 4 9 5 2 6 7 10
1 2
1 3
0 11
1 8 10 4 3 5 7 2 9 6 11
3 10
1 9 5 4 7 3 8 6 2 10
5 2
1 2```

# AI分析结果

### 题目内容
# 跳跃瓷砖
## 题目描述
### 题目大意
给定一个字符串 $s$，polycarp 想要从字符串首跳到字符串末（$s_1$ → $s_n$，其中 $n$ 表示该字符串长度）。
假设 polycarp 现在从 $a_i$ 跳到了 $a_j$，我们定义这一次跳跃的权值为 $|\text{index}(a_i) - \text{index}(a_j)|$，其中 $\text{index}$ 表示该字符在字母表中的序号（如 $\text{index}('a') = 1$，$\text{index}('z') = 26$）。
请构造出一种在保证**权值和最小**的情况下**经过的字符最多**的跳跃方案（当然，同一个字符只能经过一次，其中同一个仅指在字符串中的位置相同）。
## 样例 #1
### 输入
```
6
logic
codeforces
bca
aaaaaaaaaaa
adbaadabad
to
```
### 输出
```
9 4
1 4 3 5
16 10
1 8 3 4 9 5 2 6 7 10
1 2
1 3
0 11
1 8 10 4 3 5 7 2 9 6 11
3 10
1 9 5 4 7 3 8 6 2 10
5 2
1 2
```
### 算法分类
贪心
### 综合分析与结论
这几道题解的核心思路都是基于贪心策略。首先明确最小权值和为 $|\text{index}(s_1) - \text{index}(s_n)|$，然后考虑在这个前提下如何使经过字符最多。大家都发现应选取 $\text{index}(s_i)$ 值在 $\text{index}(s_1)$ 与 $\text{index}(s_n)$ 之间的字符，再根据 $\text{index}(s_1)$ 和 $\text{index}(s_n)$ 的大小关系进行排序。不同之处主要体现在代码实现细节，如数据存储结构、排序方式及输出处理等。
### 所选的题解
- **作者：CarroT1212 (5星)**
    - **关键亮点**：思路清晰直接，先明确最小代价，再分两种情况讨论移动步数最大的方案，代码简洁明了，使用结构体存储字符及其位置，通过排序和查找确定路径。
    - **重点代码**：
```cpp
#include <bits/stdc++.h>
#define ll long long
#define pb push_back
using namespace std;
const ll N=2e5+7;
struct node { char a; ll b; } sz[N];
bool cmp1(const node a,const node b) { return a.a==b.a?a.b<b.b:a.a<b.a; }
bool cmp2(const node a,const node b) { return a.a==b.a?a.b<b.b:a.a>b.a; }
void solve() {
    ll st,ed,n; string str;
    cin>>str;
    n=str.size();
    for (ll i=0;i<n;i++) sz[i+1]={str[i],i+1};
    if (str[0]<=str.back()) {
        sort(sz+1,sz+n+1,cmp1);
        for (ll i=1;i<=n;i++) if (sz[i].a==str[0]) { st=i; break; }
        for (ll i=n;i;i--) if (sz[i].a==str.back()) { ed=i; break; }
        printf("%lld %lld\n",(ll)(str.back()-str[0]),ed-st+1);
        for (ll i=st;i<=ed;i++) printf("%lld ",sz[i].b);
    }
    else {
        sort(sz+1,sz+n+1,cmp2);
        for (ll i=1;i<=n;i++) if (sz[i].a==str[0]) { st=i; break; }
        for (ll i=n;i;i--) if (sz[i].a==str.back()) { ed=i; break; }
        printf("%lld %lld\n",(ll)(str[0]-str.back()),ed-st+1);
        for (ll i=st;i<=ed;i++) printf("%lld ",sz[i].b);
    }
    printf("\n");
}
int main() {
    ll t; scanf("%lld",&t); while (t--) solve();
    return 0;
}
```
    - **核心实现思想**：定义结构体 `node` 存储字符及其位置，根据字符串首末字符大小关系选择不同排序方式，再通过遍历找到首末字符位置，确定路径并输出。
- **作者：Cure_Wing (4星)**
    - **关键亮点**：先以两个字符情况为基础，再讨论插入字符的情况，通过分类推理得出保持序列单调性的方案最优，代码逻辑清晰，使用结构体数组存储相关信息。
    - **重点代码**：
```cpp
#include<iostream>
#include<cstdio>
#include<algorithm>
#include<cstring>
using std::cin;using std::cout;
int t,cnt;
struct node{
    int p,id;
}ans[200005];
char s[200005];
signed main(){
    std::ios::sync_with_stdio(false);
    cin.tie(nullptr);cout.tie(nullptr);
    for(cin>>t;t--;cnt=0){
        cin>>s;
        int len=strlen(s);
        for(int i=1;i<len-1;++i) if(s[0]<=s[i]&&s[i]<=s[len-1]||s[0]>=s[i]&&s[i]>=s[len-1]) ans[++cnt].id=i+1,ans[cnt].p=s[i]-'a'+1;
        if(s[0]>=s[len-1])
            std::sort(ans+1,ans+cnt+1,[](node x,node y){return x.p>y.p;});
        else
            std::sort(ans+1,ans+cnt+1,[](node x,node y){return x.p<y.p;});
        cout<<abs(int(s[len-1]-s[0]))<<' '<<cnt+2<<'\n'<<1<<' ';
        for(int i=1;i<=cnt;++i) cout<<ans[i].id<<' ';
        cout<<len<<'\n';
    }
    return 0;
}
```
    - **核心实现思想**：遍历字符串，将符合条件（字符序号在首末字符序号之间）的字符信息存入结构体数组，根据首末字符大小关系排序，最后输出结果。
- **作者：zhicheng (4星)**
    - **关键亮点**：简洁阐述只考虑花费最小时直接从第一个跳到最后一个不劣，进而说明插入在首末字符序号之间的字符不影响花费，策略明确，代码实现简单易懂。
    - **重点代码**：
```cpp
#include<bits/stdc++.h>
using namespace std;
struct e{
    int id;
    char p;
}a[200010];
char s[200010];
bool cmp1(e a,e b){
    if(a.p!=b.p){
        return a.p<b.p;
    }
    return a.id<b.id;
}
bool cmp2(e a,e b){
    if(a.p!=b.p){
        return a.p>b.p;
    }
    return a.id<b.id;
}
int main(){
    int n,len,i,sum,u;
    scanf("%d",&n);
    while(n--){
        sum=0;
        scanf("%s",s);
        len=strlen(s);
        for(int i=0;i<=len-1;i++){
            a[i+1].id=i+1;
            a[i+1].p=s[i];
        }
        if(s[0]<s[len-1]){
            sort(a+1,a+len+1,cmp1);
        }
        else{
            sort(a+1,a+len+1,cmp2);
        }
        for(i=1;i<=len;i++){
            if(a[i].id==1){
                break;
            }
        }
        u=i;
        for(;;i++){
            sum++;
            if(a[i].id==len){
                break;
            }
        }
        printf("%d %d\n",abs(s[0]-s[len-1]),sum);
        for(i=u;;i++){
            printf("%d ",a[i].id);
            if(a[i].id==len){
                break;
            }
        }
        printf("\n");
    }
}
```
    - **核心实现思想**：用结构体数组 `a` 存储字符及其位置，根据首末字符大小关系选择排序方式，遍历确定路径上字符数量并输出路径。
### 最优关键思路或技巧
利用贪心策略，先确定最小权值和，再基于此选择在首末字符序号之间的字符，并根据首末字符大小关系进行排序来构造最优跳跃路径。在代码实现上，合理使用结构体存储字符及其位置信息，方便排序和路径查找。
### 可拓展之处
同类型题通常围绕路径规划与代价优化，类似套路是先确定最小代价的下限，再考虑如何在满足下限的情况下优化其他条件（如经过点数最多等）。可通过改变权值计算方式、路径限制条件等拓展题目。
### 洛谷相似题目推荐
- [P1080 国王游戏](https://www.luogu.com.cn/problem/P1080)
- [P1199 三国游戏](https://www.luogu.com.cn/problem/P1199)
- [P1248 加工生产调度](https://www.luogu.com.cn/problem/P1248) 

---
处理用时：66.10秒