# 题目信息

# Devu and Partitioning of the Array

## 题目描述

Devu being a small kid, likes to play a lot, but he only likes to play with arrays. While playing he came up with an interesting question which he could not solve, can you please solve it for him?

Given an array consisting of distinct integers. Is it possible to partition the whole array into $ k $ disjoint non-empty parts such that $ p $ of the parts have even sum (each of them must have even sum) and remaining $ k $ - $ p $ have odd sum? (note that parts need not to be continuous).

If it is possible to partition the array, also give any possible way of valid partitioning.

## 样例 #1

### 输入

```
5 5 3
2 6 10 5 9
```

### 输出

```
YES
1 9
1 5
1 10
1 6
1 2
```

## 样例 #2

### 输入

```
5 5 3
7 14 2 9 5
```

### 输出

```
NO
```

## 样例 #3

### 输入

```
5 3 1
1 2 3 7 5
```

### 输出

```
YES
3 5 1 3
1 7
1 2
```

# AI分析结果

### 题目内容
# Devu和数组划分

## 题目描述
Devu还是个小孩子，喜欢玩，不过他只喜欢玩数组。玩耍时，他想出了一个有趣的问题，但他自己解不出来，你能帮他解决吗？

给定一个由不同整数组成的数组。是否有可能将整个数组划分为 $k$ 个不相交的非空部分，使得其中 $p$ 个部分的和为偶数（每个部分的和都必须是偶数），其余 $k - p$ 个部分的和为奇数？（注意，这些部分不需要是连续的）。

如果可以划分该数组，还请给出任何一种有效的划分方式。

## 样例 #1
### 输入
```
5 5 3
2 6 10 5 9
```
### 输出
```
YES
1 9
1 5
1 10
1 6
1 2
```

## 样例 #2
### 输入
```
5 5 3
7 14 2 9 5
```
### 输出
```
NO
```

## 样例 #3
### 输入
```
5 3 1
1 2 3 7 5
```
### 输出
```
YES
3 5 1 3
1 7
1 2
```

### 算法分类
构造

### 综合分析与结论
这些题解的核心思路都是先将数组中的奇数和偶数分开，然后根据奇数和偶数的数量以及 $k$ 和 $p$ 的值来判断是否能够进行划分，并尝试构造出满足条件的划分方案。
1. **思路**：大部分题解都先将奇数和偶数分别存储，然后依据奇数、偶数的个数与 $k - p$、$p$ 的关系判断能否划分。比如，若奇数个数不足 $k - p$ 个，或奇数个数为奇数导致有多余奇数，或偶数个数不足（偶数个数 +（剩余奇数个数 $\div$ 2）$< p$），则无解。
2. **算法要点**：在构造划分方案时，先在 $k - p$ 个奇数堆中各放一个奇数，在 $p$ 个偶数堆中，优先每个堆放一个偶数，偶数不足则用两个奇数凑。若有剩余数字，由于偶数不改变奇偶性，奇数两两组合为偶数，所以可将剩余数字放到某一堆中。
3. **解决难点**：主要难点在于全面考虑无解的情况，如某些题解因未考虑 $p = 0$ 等特殊情况而 WA。同时，合理构造划分方案，保证满足奇偶性要求也是重点。

### 所选的题解
#### 作者：fyn1234（5星）
- **关键亮点**：思路清晰，代码简洁明了，先将奇数和偶数分别存入队列，通过简单的数学判断确定无解情况，之后按规则构造划分方案，逻辑连贯，易于理解。
- **重点代码**：
```cpp
#include<bits/stdc++.h>
using namespace std;
const int N = 1e5+5;
queue<int> ou,ji;
long long oou,jji;
vector<int> ans[N];
int main(){
    long long n,k,p;
    cin>>n>>k>>p;
    for(int i = 1;i<=n;i++){//输入
        long long x;
        cin>>x;
        if(x%2==0){
            ++oou;
            ou.push(x);
        } 
        else {
            ++jji;
            ji.push(x);
        }
    }
    long long need = k-p;
    if(jji<need || (jji-need)%2!=0 || oou+(jji-need)/2<p){//判断无解的情况
        cout<<"NO";
        return 0;
    }
    for(int i = 1;i<=need;i++){//放奇数
        ans[i].push_back(ji.front());
        ji.pop();
    }
    for(int i = need+1;i<=k;i++){//放偶数
        if(!ou.empty()){
            ans[i].push_back(ou.front());
            ou.pop();
        }
        else{
            ans[i].push_back(ji.front());
            ji.pop();
            ans[i].push_back(ji.front());
            ji.pop();
        }
    }
    while(!ou.empty()){//放剩余的偶数
        ans[1].push_back(ou.front());
        ou.pop();
    }
    while(!ji.empty()){//放剩余的奇数
        ans[1].push_back(ji.front());
        ji.pop();
    }
    cout<<"YES"<<endl;
    for(int i = 1;i<=k;i++){
        cout<<ans[i].size();
        for(auto j:ans[i]) cout<<" "<<j;
        cout<<endl;
    }
    return 0;
}
```
- **核心实现思想**：先统计奇数和偶数个数，判断无解情况。然后在奇数堆放入奇数，偶数堆优先放偶数，不够则用奇数凑，最后处理剩余数字。

#### 作者：huangxianghui（4星）
- **关键亮点**：详细地考虑了各种无解情况，对每种情况都有清晰的解释，构造方案时对不同情况（偶数多、偶数少等）分别处理，逻辑较全面。
- **重点代码**：
```cpp
#include<bits/stdc++.h>
#define f(i,a,b) for (int i=a;i<=b;i++)
#define ll long long
using namespace std;
const int maxn=1e5+10;
int n,k,p,num;
int a[maxn],len1,len2;
bool l[maxn];
vector<int> qi,ou;
ll sum;
inline ll read()
{
    ll l=0,f=1;
    char c=getchar();
    while (c<'0' || c>'9')
    {
        if (c=='-') f=-1;
        c=getchar();
    }
    while (c>='0' && c<='9') l=(l<<3)+(l<<1)+(c^48),c=getchar();
    return l*f;
}
int main()
{
    n=read(),k=read(),p=read();
    f(i,1,n)
    {
        a[i]=read(),sum+=a[i];
        if (a[i]%2) qi.push_back(a[i]);
        else ou.push_back(a[i]);
    }
    len1=qi.size(),len2=ou.size();
    if (len1<k-p || sum%2!=(k-p)%2) cout<<"NO";
    else
    {
        if (len2<p && (len1-((p-len2)*2))<(k-p)) cout<<"NO";
        else
        {
            cout<<"YES"<<endl;
            num=0;
            int po=1;
            while (po<p && num<len2) cout<<1<<' '<<ou[num]<<endl,po++,num++;//前面所有偶数堆只放一个偶数
            if (num<len2)//偶数多出来了
            {
                if (po<=p)//前面还没塞满
                {
                    cout<<len2-num+(((len1-(k-p))>0)?(len1-(k-p)):0)<<' ';//连着多出来的奇数全部给他塞到最后一个偶数堆，由于前面已经判断过NO，所以这里相安无事。
                    for (int i=num; i<len2; i++) cout<<ou[i]<<' ';
                    for (num=0; num<len1-(k-p); num++) cout<<qi[num]<<' ';
                    cout<<endl;
                    for (; num<len1; num++) cout<<1<<' '<<qi[num]<<endl;//剩下的奇数堆每堆只放一个奇数
                }
                else//前面塞满了
                {
                    cout<<len2-num+1<<' ';//偶数塞到下一个奇数堆，再配一个奇数
                    for (int i=num; i<len2; i++) cout<<ou[i]<<' ';
                    cout<<qi[0]<<' ';
                    cout<<endl;
                    for (num=1,po=1; po<(k-p); po++,num++) cout<<"1 "<<qi[num]<<endl;//只放一个奇数
                    if (len1-num>0)//多出来的放到最后一堆
                    {
                        cout<<len1-num<<' ';
                        for (; num<len1; num++) cout<<qi[num]<<' ';
                    }
                }
            }
            else//偶数少了
            {
                for (num=0; num<len1 && po<p; num+=2,po++) cout<<2<<' '<<qi[num]<<' '<<qi[num+1]<<endl;//用奇数凑偶数
                if (po<=p && (len1-num)-(k-p)>0)
                {
                    cout<<(len1-num)-(k-p)<<' ';
                    for (; num<len1-(k-p); num++) cout<<qi[num]<<' ';//多出来的放到最后一个偶数堆，后面相安无事
                    cout<<endl;
                    for (; num<len1; num++) cout<<1<<' '<<qi[num]<<endl;
                }
                else
                {
                    for (po=0; po<(k-p-1); num++,po++) cout<<1<<' '<<qi[num]<<endl;//跟前面一样
                    cout<<len1-num<<' ';
                    for (; num<len1; num++) cout<<qi[num]<<' ';//仍然丢到最后一堆
                }
            }
        }
    }
}
```
- **核心实现思想**：先判断无解情况，再根据偶数个数与 $p$ 的关系，分别处理偶数多和偶数少的情况，构造划分方案。

#### 作者：longlong_int（4星）
- **关键亮点**：对判断 YES/NO 的条件分析清晰，通过计算数列所有整数之和与 $k - p$ 的同余关系来初步判断，然后分偶数和奇数部分分别构造，逻辑严谨。
- **重点代码**：
```cpp
#include <bits/stdc++.h>
#define endl '\n'
#define int long long
using namespace std;

const int N = 1e5 + 10;
int arr[N];
vector<int> odd, even;

signed main()
{
    int n, k, p;
    cin >> n >> k >> p;
    int sum = 0;
    for (int i = 1; i <= n; i++)
    {
        cin >> arr[i];
        sum += arr[i];
        if (arr[i] & 1)
            odd.push_back(arr[i]);
        else
            even.push_back(arr[i]);
    }
    string s;
    if (((k - p) & 1) ^ (sum & 1))
    {
        cout << "NO\n";
        return 0;
    }
    else
        s += "YES\n";

    for (int i = 1; i < p; i++) 
    {
        if (even.empty())
        {
            if (odd.empty())
            {
                cout << "NO" << endl;
                return 0;
            }
            int a = odd.back();
            odd.pop_back();
            if (odd.empty())
            {
                cout << "NO" << endl;
                return 0;
            }
            int b = odd.back();
            odd.pop_back();
            s += "2 " + to_string(a) + " " + to_string(b) + endl;
        }
        else
        {
            s += "1 " + to_string(even.back()) + endl;
            even.pop_back();
        }
    }

    if (k!= p)
    {
        if (p!= 0)
        {
            if (even.empty())
            {
                if (odd.empty())
                {
                    cout << "NO" << endl;
                    return 0;
                }
                int a = odd.back();
                odd.pop_back();
                if (odd.empty())
                {
                    cout << "NO" << endl;
                    return 0;
                }
                int b = odd.back();
                odd.pop_back();
                s += "2 " + to_string(a) + " " + to_string(b) + endl;
            }
            else
            {
                s += "1 " + to_string(even.back()) + endl;
                even.pop_back();
            }
        }
        for (int i = 1; i <= (k - p - 1); i++)
        {
            if (odd.empty())
            {
                cout << "NO" << endl;
                return 0;
            }
            s += "1 " + to_string(odd.back()) + endl;
            odd.pop_back();
        }
    }

    if ((odd.size() + even.size()))
    {
        s += to_string(odd.size() + even.size()) + " ";
        for (int i : odd)
        {
            s += to_string(i) + " ";
        }
        for (int i : even)
        {
            s += to_string(i) + " ";
        }
    }
    cout << s << endl;
    return 0;
}
```
- **核心实现思想**：先判断总和与 $k - p$ 的奇偶关系，再分别为偶数堆和奇数堆分配数字，最后处理剩余数字。

### 最优关键思路或技巧
1. **奇偶性判断**：通过分析所有数总和的奇偶性与 $k - p$ 的奇偶性是否一致，快速排除部分无解情况。
2. **分开处理奇数和偶数**：将数组中的奇数和偶数分开存储和处理，利用奇数 + 奇数 = 偶数、偶数 + 偶数 = 偶数、奇数 + 偶数 = 奇数的特性来构造满足条件的划分。
3. **边界情况处理**：全面考虑各种边界条件，如奇数个数不足、偶数个数不足、$p = 0$ 等特殊情况，避免遗漏导致错误。

### 同类型题或类似算法套路
此类题目属于构造类型题目，通常需要根据给定的条件，合理利用数字特性（如奇偶性）来构造出满足要求的方案。类似套路包括先分析题目条件，找出关键限制因素（如本题的奇偶性和堆的数量关系），然后根据这些因素对数据进行分类处理（如分开奇数和偶数），在构造过程中要充分考虑各种可能的边界情况。

### 洛谷相似题目推荐
1. [P1149 火柴棒等式](https://www.luogu.com.cn/problem/P1149)：通过枚举和构造满足火柴棒数量限制的等式，与本题类似，需根据条件构造出符合要求的方案。
2. [P1469 找筷子](https://www.luogu.com.cn/problem/P1469)：利用异或运算的特性来找出数组中唯一出现奇数次的数，与本题利用数字特性（奇偶性）解决问题的思路相似。
3. [P2678 [NOIP2015 提高组] 跳石头](https://www.luogu.com.cn/problem/P2678)：通过二分答案并构造符合条件的方案，与本题构造划分方案的思路有一定相似性，都需要根据条件进行合理构造。

### 个人心得摘录与总结
1. **作者：Naganorhara_Yoimiya**：最初代码 WA 是因为未考虑 $p = 0$ 的情况，对偶数多余时放置位置的处理不够全面，应根据 $p$ 是否为 $0$ 来决定将多余偶数放在奇数堆还是偶数堆。总结出在处理类似问题时，要全面考虑特殊情况，对各种条件分支进行细致分析，避免遗漏特殊情况导致错误。 

---
处理用时：130.85秒