# 题目信息

# [AHOI2017初中组] alter

## 题目描述

有 $n$ 盏灯排成一列，其中有些灯开着，有些灯关着。小可可希望灯是错落有致的，他定义一列灯的状态的不优美度为这些灯中最长的连续的开着或关着的灯的个数。小可可最多可以按开关 $k$ 次，每次操作可以使该盏灯的状态取反：原来开着的就关着，反之开着。现在给出这些灯的状态，求操作后最小的不优美度。

## 说明/提示

$30\%$ 的数据：$1\le k \le n\le20$；

$50\%$ 的数据：$1\le k \le n\le300$；

另有 $15\%$ 的数据：$1\le k \le n\le 10^5$，字符串为全 `N` 或全 `F`；

$100\%$ 的数据：$1\le k \le n\le 10^5$。

本题已经加入 hack 数据。

## 样例 #1

### 输入

```
8 1
NNNFFNNN```

### 输出

```
3```

# AI分析结果

### 综合分析与结论
本题的核心在于求解经过最多 $k$ 次操作后，灯序列的最小不优美度。由于答案具有单调性，大部分题解采用二分答案的方法来解决。在实现过程中，关键在于处理二分的判定条件和对最小不优美度为 1 的情况进行特判。

### 所选题解
- **作者：Sooke (赞：38)，4星**
  - **关键亮点**：思路清晰，对二分过程和特判情况的解释详细，代码简洁易懂。
  - **个人心得**：提到自己被坑了好几次才AC，强调了二分中几个坑点，如最小值为 1 时的特判、最多按几次灯的理解以及超过可能不优美度时赋值的注意事项。
- **作者：Happy_Every_day (赞：7)，4星**
  - **关键亮点**：对三种情况的讨论全面，将输入字符串中相同且连续的字符数用数组记录，方便后续计算操作次数，代码实现逻辑清晰。
  - **个人心得**：无。
- **作者：FreeTimeLove (赞：2)，4星**
  - **关键亮点**：对二分过程和判断可行性的分析详细，特别是对 $mid\ge2$ 和 $mid = 1$ 两种情况的处理分别进行了说明，逻辑严谨。
  - **个人心得**：无。

### 重点代码
#### Sooke的代码
```cpp
#include <iostream>
using namespace std;
int main()
{
    int n,k,p=0,g,t,ans;
    char c[2]={'F','N'}; 
    string s;
    cin >> n >> k >> s;
    for(int i=0;i < n;i++)
    if(s[i] == c[i % 2]) p++;
    if(p <= k || n-p <= k)
    {cout << 1; return 0;}
    int lb=2,rb=n / k+1,mb; 
    while(lb <= rb)
    {
        mb=(lb+rb) / 2; 
        g=0;
        for(int i=0,j=0,l=0;i < n;i++)
        {
            if(s[j] == s[i]) l++;
            else j=i,l=1;
            if(mb < l) j=i+1,l=0,g++;
        }
        if(g <= k)
        {
            rb=mb-1;
        } else
            lb=mb+1;
    }
    cout << lb;
    return 0;
}
```
**核心实现思想**：先特判最小不优美度为 1 的情况，然后二分可能的不优美度，在二分过程中遍历灯序列，统计需要按开关的次数，根据次数调整二分区间。

#### Happy_Every_day的代码
```cpp
#include <cstdio>
using namespace std;
char s[100010];
int n,k,Left,Right,Mid,i,j,a[100010],Cnt,Suma,Sumb; 
int read () {
    int k=0,f=1;
    char c=getchar ();
    while (c<'0'||c>'9') {if (c=='-') f=-1;c=getchar ();}
    while (c>='0'&&c<='9') {k=k*10+c-'0';c=getchar ();}
    return k*f;
}
bool Check (int Ans) {
    int i,S;
    for (i=1,S=0;i<=Cnt;i++) S=S+a[i]/(Ans+1);
    if (S<=k) return true;else return false;
}
int main () {
    n=read ();k=read ();
    scanf ("%s",s+1);
    for (i=1;i<=n;i++) if ((i%2==1&&s[i]=='N')||(i%2==0&&s[i]=='F')) Suma++;
    for (i=1;i<=n;i++) if ((i%2==0&&s[i]=='N')||(i%2==1&&s[i]=='F')) Sumb++;
    if (Suma<=k||Sumb<=k) {puts ("1");return 0;}
    for (i=1;i<=n;i++) {
        a[++Cnt]=1;
        while (s[i]==s[i+1]) {a[Cnt]++;i++;} 
    }
    Left=2;Right=n;
    while (Left<=Right) {
        Mid=(Left+Right)>>1;
        if (Check (Mid)==false) 
            Left=Mid+1;
        else 
            Right=Mid-1;
    }
    printf ("%d\n",Left);
    return 0;
}
```
**核心实现思想**：先特判最小不优美度为 1 的情况，然后将输入字符串中相同且连续的字符数用数组 `a` 记录，二分可能的不优美度，在判断函数 `Check` 中计算需要操作的次数，根据次数调整二分区间。

#### FreeTimeLove的代码
```cpp
#include<iostream>
#include<cstdio>
#include<cstring>
#include<algorithm>
#include<queue>
#define ll long long
using namespace std;
const int N=1e5+5;
int n,k,x,tot,sum,num,ans,que[N],a[N],l,r,maxn;
char s[N];
bool ok(int lim){
    x=lim+1,ans=0;
    for(int i=1;i<=tot;i++)
        ans+=que[i]/x;
    return ans<=k;
}
int main(){
    cin>>n>>k;
    getchar();
    for(int i=1;i<=n;++i)s[i]=getchar();
    for(int i=1;i<=n;i++){
        a[i]=(s[i]=='N')?1:0;
        if((i+a[i])%2)ans++;
    }
    a[n+1]=2;
    if(ans<=k||(n-ans)<=k){
        cout<<1<<endl;
        return 0;
    }
    
    sum=1,num=a[1];
    for(int i=2;i<=n+1;i++){
        if(a[i]==num)sum++;
        else{
            que[++tot]=sum;
            num=a[i];
            maxn=max(maxn,sum);	
            sum=1;
        }
    }
    l=2,r=maxn;
    while(l<r){
        int mid=(l+r)>>1;
        if(ok(mid))r=mid;
        else l=mid+1;
    }
    cout<<l<<endl;
    return 0;
}
```
**核心实现思想**：先特判最小不优美度为 1 的情况，然后将输入字符串转化为每个连串的长度构成的序列 `que`，二分可能的不优美度，在判断函数 `ok` 中计算需要反转的字符数，根据字符数调整二分区间。

### 最优关键思路或技巧
- **二分答案**：利用答案的单调性，通过二分缩小答案范围，将问题转化为判断某个答案是否可行。
- **特判最小不优美度为 1 的情况**：由于最小不优美度为 1 时的情况特殊，需要单独处理，避免二分过程中出现错误。
- **预处理连续相同字符的长度**：将输入字符串中相同且连续的字符数用数组记录，方便后续计算需要操作的次数。

### 可拓展之处
同类型题或类似算法套路：
- 涉及最大值最小化或最小值最大化的问题，通常可以考虑使用二分答案的方法。
- 在二分过程中，需要根据具体问题设计合理的判断函数，判断某个答案是否可行。

### 推荐题目
- [P1873 砍树](https://www.luogu.com.cn/problem/P1873)：二分答案求解最大值最小化问题。
- [P2678 跳石头](https://www.luogu.com.cn/problem/P2678)：二分答案结合贪心算法求解最小值最大化问题。
- [P3853 [TJOI2007]路标设置](https://www.luogu.com.cn/problem/P3853)：二分答案解决最小值最大化问题。

### 个人心得总结
- **Sooke**：强调了二分中的几个坑点，如最小值为 1 时的特判、最多按几次灯的理解以及超过可能不优美度时赋值的注意事项，提醒在解题过程中要注意细节。

---
处理用时：60.51秒