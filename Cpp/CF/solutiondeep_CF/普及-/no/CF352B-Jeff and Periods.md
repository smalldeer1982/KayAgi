# 题目信息

# Jeff and Periods

## 题目描述

One day Jeff got hold of an integer sequence $ a_{1} $ , $ a_{2} $ , $ ... $ , $ a_{n} $ of length $ n $ . The boy immediately decided to analyze the sequence. For that, he needs to find all values of $ x $ , for which these conditions hold:

- $ x $ occurs in sequence $ a $ .
- Consider all positions of numbers $ x $ in the sequence $ a $ (such $ i $ , that $ a_{i}=x $ ). These numbers, sorted in the increasing order, must form an arithmetic progression.

Help Jeff, find all $ x $ that meet the problem conditions.

## 说明/提示

In the first test $ 2 $ occurs exactly once in the sequence, ergo $ p_{2}=0 $ .

## 样例 #1

### 输入

```
1
2
```

### 输出

```
1
2 0
```

## 样例 #2

### 输入

```
8
1 2 1 3 1 2 1 5
```

### 输出

```
4
1 2
2 4
3 0
5 0
```

# AI分析结果

### 题目内容
# Jeff和周期

## 题目描述
一天，Jeff得到了一个长度为n的整数序列$a_1$，$a_2$，... ，$a_n$。这个男孩立刻决定分析这个序列。为此，他需要找到所有满足以下条件的$x$值：
- $x$出现在序列$a$中。
- 考虑序列$a$中数字$x$的所有位置（即满足$a_i = x$的$i$）。这些数字按升序排序后，必须形成一个等差数列。

帮助Jeff找到所有符合问题条件的$x$。

## 说明/提示
在第一个测试中，2在序列中恰好出现一次，因此$p_2 = 0$。

## 样例 #1
### 输入
```
1
2
```
### 输出
```
1
2 0
```

## 样例 #2
### 输入
```
8
1 2 1 3 1 2 1 5
```
### 输出
```
4
1 2
2 4
3 0
5 0
```

### 算法分类
模拟

### 综合分析与结论
这些题解的核心思路都是围绕判断序列中每个出现的数，其出现位置是否构成等差数列展开。大部分题解利用数组或`vector`等数据结构记录每个数出现的位置，在输入过程中或输入完成后判断是否满足等差数列条件，同时注意对只出现一次的数进行特判（公差为0）。各题解在实现细节上略有不同，比如记录信息的数据结构选择、判断等差数列的时机等，但整体思路较为一致。

### 所选的题解
- **作者：PR_CYJ（5星）**
    - **关键亮点**：思路清晰，代码简洁明了。通过三个数组分别记录数的上一次出现位置、是否构成等差数列以及公差，在$O(n)$时间复杂度内完成判断和结果输出，注释详细。
    - **重点代码**：
```cpp
#include<bits/stdc++.h>
using namespace std;
int main()
{
    int n,ans=0,m=0;
    cin>>n;
    int a[n+10]={};
    for(int i=1;i<=n;i++)
    {
        cin>>a[i];
        m=max(m,a[i]);//求最大数 
    }
    m+=10;//避免数组越界 
    int lt[m]={},d[m]={};
    bool f[m]={};//三个数组的详细含义请看思路部分 
    for(int i=1;i<=n;i++)
    {
        if (lt[a[i]]!=0)//特判第一次出现的情况（即上一次出现位置为 0） 
        {
            if (d[a[i]]==0)//特判第二次出现的情况（即公差为 0） 
                d[a[i]]=i-lt[a[i]];
            else if (i-lt[a[i]]!=d[a[i]])
                f[a[i]]=true;
        }
        lt[a[i]]=i;//更新上一次出现的位置 
    }
    for(int i=1;i<m;i++)//注意是i<m，否则会数组越界 
        if (lt[i]!=0&&!f[i])//lt数组也可用于判断该数是否出现 
            ans++;
    cout<<ans<<endl;
    for(int i=1;i<m;i++)
        if (lt[i]!=0&&!f[i])
            cout<<i<<" "<<d[i]<<endl;//输出答案 
}
```
    - **核心实现思想**：遍历数组，利用`lt`数组记录每个数上一次出现位置，`d`数组记录公差，`f`数组标记是否构成等差数列。遍历过程中根据条件更新数组，最后统计并输出满足条件的数及其公差。
- **作者：The_jester_from_Lst（4星）**
    - **关键亮点**：对暴力模拟优化思路阐述清晰，通过另开数组记录每个数上次出现位置和公差，在遍历中维护并判断，将时间复杂度降至$O(nlogn)$，代码中包含输入输出优化。
    - **重点代码**：
```cpp
#include<bits/stdc++.h>
#define int long long
using namespace std;
inline int rd(){
    int jya=0,ysc=1;char ch=getchar();
    while(!isdigit(ch)){if(ch=='-')ysc=-1;ch=getchar();}
    while(isdigit(ch)){jya=jya*10+(ch-'0');ch=getchar();}
    return jya*ysc;
}
inline void wr(int x){
    if(x<0)putchar('-'),x=-x;
    if(x>9)wr(x/10);
    putchar(x%10+'0');
}
struct node{
    int x,y;
}ans[100086];
int n,a[100086],b[100086],s,vis[100086],cha[100086];
inline bool cmp(node x,node y){
    return x.x<y.x;
}
signed main(){
    n=rd();
    for(int i=1;i<=n;++i)a[i]=rd();
    for(int i=1;i<=n;++i){
        if(cha[a[i]]==-1)continue;//已经排除了就不要搜了
        if(vis[a[i]]==0){
            vis[a[i]]=i;
            continue;
        } //特判第一次访问
        if(cha[a[i]]==0)cha[a[i]]=i-vis[a[i]]; //特判
        else {
            if(cha[a[i]]!=i-vis[a[i]]){
                cha[a[i]]=-1;
                continue;
            }
        }
        vis[a[i]]=i;
    }
    for(int i=1;i<=n;++i){
        if(cha[a[i]]!=-1){
            ans[++s].x=a[i];
            ans[s].y=cha[a[i]];
            cha[a[i]]=-1; //去重
        }
    }
    sort(ans+1,ans+1+s,cmp);
    wr(s);putchar('\n');
    for(int i=1;i<=s;++i){
        wr(ans[i].x);
        putchar(' ');
        wr(ans[i].y);
        putchar('\n');
    }
    return 0;
}
```
    - **核心实现思想**：遍历数组，利用`vis`数组记录每个数上次出现位置，`cha`数组记录公差。在遍历过程中，根据条件判断并更新`cha`数组，最后将满足条件的数及其公差存入结构体数组并排序输出。
- **作者：hcy1117（4星）**
    - **关键亮点**：思路清晰，通过`pre`数组维护数字上一次出现位置，`num`数组维护公差，同时利用`f`数组去重，代码简洁，注释详细。
    - **重点代码**：
```cpp
#include<bits/stdc++.h>
using namespace std;
int n;
int a[100005],pre[100005],num[100005];//前面提到过，不记得的话返回去看看 
bool f[100005];//用来去重 
int main()
{
    cin>>n;
    for(int i=1;i<=n;i++)
    {
        cin>>a[i];
        int x=i-pre[a[i]]; //计算公差 
        if(pre[a[i]]==0)x=0; //特殊处理 
        if(num[a[i]]!=-1&&num[a[i]]!=x) //与之前算出的公差不相等 
        {
            if(num[a[i]]==0)num[a[i]]=x; //第一次 
            else num[a[i]]=-1; //不是等差序列 
        }
        pre[a[i]]=i; //更新位置 
    }
    //f数组的用处就是因为数字x可能在a中出现多次但只能记一次，所以要去重 
    int cnt=0;
    for(int i=1;i<=n;i++)
    {
        if(num[a[i]]!=-1&&!f[a[i]])
        {
            ++cnt;
            f[a[i]]=1;
        }
    }
    cout<<cnt<<endl;
    for(int i=1;i<=100000;i++)
    {
        if(f[i]==1)
        {
            cout<<i<<" "<<num[i]<<endl;
        }
    }
    return 0;
}
```
    - **核心实现思想**：遍历数组，在遍历过程中利用`pre`数组更新每个数上一次出现位置，计算公差并与`num`数组中记录的公差对比，不相等则标记`num`为$-1$，最后利用`f`数组去重并统计输出满足条件的数及其公差。

### 最优关键思路或技巧
利用数组记录每个数出现位置相关信息（如上次出现位置、公差等），在遍历输入序列过程中实时判断是否满足等差数列条件，这样可以将时间复杂度控制在$O(n)$级别，同时注意对特殊情况（如只出现一次的数）的处理。

### 可拓展之处
此类题目属于模拟类型，类似套路可应用于其他需要对序列中元素位置关系进行判断的题目，比如判断元素出现位置是否构成等比数列等。

### 洛谷相似题目推荐
- [P1036 选数](https://www.luogu.com.cn/problem/P1036)：通过枚举组合判断是否满足质数条件，考察枚举和数论知识。
- [P1161 开灯](https://www.luogu.com.cn/problem/P1161)：模拟开关灯操作，与本题类似之处在于对序列元素状态的改变与判断。
- [P1423 小玉在游泳](https://www.luogu.com.cn/problem/P1423)：根据给定规则模拟小玉游泳过程，同样是模拟类题目。 

---
处理用时：81.43秒