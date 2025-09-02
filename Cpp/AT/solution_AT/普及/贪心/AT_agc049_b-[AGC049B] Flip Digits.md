# [AGC049B] Flip Digits

## 题目描述

[problemUrl]: https://atcoder.jp/contests/agc049/tasks/agc049_b

`0` と `1` からなる長さ $ N $ の文字列 $ S $ 及び $ T $ が与えられます． あなたは，$ S $ に以下の操作を好きな回数行うことができます．

- $ S_i= $`1` となる $ i $ ($ 2\ \leq\ i\ \leq\ N $) を選ぶ． そして，$ S_i $ を `0` で置き換える． さらに，$ S_{i-1} $ を今と異なる文字へ変更する．つまり，操作の直前で $ S_{i-1} $ が `0` であれば `1` に，`1` であれば `0` に変更する．

$ S $ を $ T $ に一致させることは可能でしょうか？ また可能な場合は，そのために必要な最小の操作回数はいくらでしょうか？

## 说明/提示

### 制約

- $ 1\ \leq\ N\ \leq\ 5\ \times\ 10^5 $
- $ S $ は `0`,`1` からなる長さ $ N $ の文字列．
- $ T $ は `0`,`1` からなる長さ $ N $ の文字列．

### Sample Explanation 1

`001` → ($ i=3 $ で操作) → `010` → ($ i=2 $ で操作) → `100` とすればよいです．

## 样例 #1

### 输入

```
3
001
100```

### 输出

```
2```

## 样例 #2

### 输入

```
3
001
110```

### 输出

```
-1```

## 样例 #3

### 输入

```
5
10111
01010```

### 输出

```
5```

# 题解

## 作者：Zhl2010 (赞：2)

## 题目概括
将一个子串用最少的次数反转成另一个子串。
## 思路
这种题肯定不能暴力（数据范围太大了），那就只能**贪心**了。

这道题因为是 `01` 串，所以只有两种情况，`01->10` 和 `00->11`。

贪心思路：从 $1$ 到 $n$ 遍历，如果不相同就要操作：找到离它最近的 $1$ 一直向它取反过来，也就是通过 `01->10` 将 $1$ 传过来。

还有，此题并不需要考虑顺序，所以贪心是对的。

**提示**：记得开 `long long`。

## 代码+注释
```cpp
#include<bits/stdc++.h>
#define int long long//十年OI...，不开long long... 
using namespace std;
int n,b,ans;
char s[500010],t[500010];
signed main(){
    cin>>n>>s>>t;
    for(int i=0;i<n;i++){
    	int pd=0,a=0;
        if(s[i]==t[i])continue;//只有不等于时才需要操作 
		for(int j=max(i+1,b);j<n;j++){
			if(s[j]=='1'&&!pd){//寻找离它最近的 1 
				a=j;
				break;
			}
		}
		b=a+1;
		if(b==1){//没有 1 了，所以无法完成 
			cout<<-1<<endl;
			return 0;//直接结束 
		}
		ans+=a-i;//a-i是每次操作所需步数 
		s[a]='0';//转换后 1 就变成 0 了 
		s[i]=t[i];//转换后两个子串的第 i 为也就相等了 
	}
	cout<<ans<<endl;
	return 0;
}
```

---

## 作者：nkrqzjc_zzz (赞：2)

### [题目链接](https://www.luogu.com.cn/problem/AT_agc049_b)

------------

### 写在前面：

这道题其实码量和思想都是只有橙的，就是有点点小坑而已。

------------

### 思路：

我们可以发现，这道题的操作无非就两种，我们设原字符串的某一位为 $a_i$，我们需要改变的字符串某一位设为 $b_i$。

第一种情况就是当 $a_i\neq b_i$ 且 $a_{i+1}\neq b_{i+1}$ 时，我们使用一次操作，便可以成功将 $11$ 的状态变成 $00$。

第二种情况就是当 $a_i\neq b_i$ 但 $a_{i+1}=b_{i+1}$ 时，我们使用一次操作，便可以成功将 $01$ 的状态变成 $10$。

此时我们理所应当的就可以想到贪心算法了，我们从头到尾遍历一遍，如果不相同就进行操作，找到离他最近的 $1$ 一直取反过来，想要证明这个算法的正确性也比较简单。

我们可以这样想，假设我进行了 $x$ 次操作，这 $x$ 次操作是否有在顺序上的限制，答案是没有的。因为我们对某两位做的操作就仅仅只有翻转它们的值，假设我对 $a_y$ 为做了 $x$ 次操作，当 $x$ 为偶数时，$a_y$ 不变。当 $x$ 为奇数时，$a_y$ 取反。所以只要操作的位置相同，顺序是可以打乱的。

那么我们就可以实现了，每一次枚举一个位置，如果这个位置的两个字符相等，就直接枚举下一个位置。如果不相等，就找到离它最近的 $1$，进行转换。

### 代码：

我前面说了这么多，~~会有人看嘛？~~

那么你们爱的来了。（还压过行哟，完美！）

```cpp
#include<bits/stdc++.h>
int n,a,b,pa,ji;
long long c;
char s[500002],t[500002];
main(){
    cin>>n>>s>>t;
    for(int i=0;i<n&&!pa;i++){
    	ji=0,a=0;
        if(s[i]==t[i])continue;
		for(int j=max(i+1,b);j<n;j++)if(s[j]=='1'&&!ji){a=j;break;}
		b=a+1;
		if(b==1)puts("-1"),pa=1;
		c=c+a-i,s[a]='0',s[i]=t[i];
	}
	if(!pa)printf("%lld",c);
}
```


---

## 作者：Miracle_1024 (赞：1)

## 思路
按照题目，一共分为两种情况：$01$ 变 $10$ 和 $11$ 变 $00$。

情况 $1$ 就是把 $1$ 都往左移，情况 $2$ 则是选择一个 $1$，将其左移一位，如果左边有 $1$ 就抵消掉它们。

实现：从左到右扫一遍，把 $T$ 中的 $1$ 存起来，然后找 $S$ 中的 $1$ 匹配 $T$ 中的 $1$，判断是否消除了所以的 $1$。

## 代码：

```cpp
#include<bits/stdc++.h>
#define ll long long
using namespace std;
const int N=1e6+10;
const int INF=0x3f3f3f3f;
inline int read(){ll x=0,f=1;char ch=getchar();while (ch<'0'||ch>'9'){if (ch=='-') f=-1;ch=getchar();}while (ch>='0'&&ch<='9'){x=x*10+ch-48;ch=getchar();}return x*f;}
ll n,ans,j=1;
bool flag;
string a,b;
int main(){
    cin>>n>>a>>b;
    for(int i=0;i<n;i++){
        if(a[i]!=b[i]){
            j=max((ll)i+1,j);
            while(a[j]!='1'&&j<=n-1){
                j++;
            }
            if(a[j]!='1'||j==n){
                flag=1;
                break;
            }
            a[j]='0';
            ans+=j-i;
            j++;
        }
    }
    if(flag)cout<<-1<<endl;
    else cout<<ans<<endl;
}

```

---

## 作者：a18981826590 (赞：1)

# [[AGC049B] Flip Digits](https://www.luogu.com.cn/problem/AT_agc049_b)
## 题意简述
给定一个长度为 $n$ 的由 `01` 组成的字符串 $a$，进行若干次操作，每次任取一个 $i$（$1<i \le n$），对 $a_{i-1}$ 和 $a{i}$ 取反，求能否得到字符串 $b$ 并求出最小操作次数。
## 解题思路
字符串长度 $1 \le n \le 5 \times 10^{5}$，暴力模拟肯定不行了。

可以考虑贪心，从头扫过去，遇到不同的就修改，但怎么修改呢？

题目中的操作其实只有两种：

1. `01` 变为 `10`，可以把后面的 $1$ 传到前面去；
2. `11` 变为 `00`；

那就很简单了。分为以下两种情况：

1. 如果 $a_{i}$ 为 $0$ 且 $b_{i}$ 为 $1$，就找到 $a$ 中 $i$ 后面第一个 $1$（令它为 $a_{j}$），用操作一把它传到 $i$，操作数为 $j-i$；
2. 如果 $a_{i}$ 为 $1$ 且 $b_{i}$ 为 $0$，就找到 $a$ 中 $i$ 后面第一个 $1$（令它为 $a_{j}$），用操作一把它传到 $i+1$，操作数为 $j-i-1$，再用操作二把 $a_{i}$ 和 $a_{i+1}$ 转为 $0$，操作数为 $1$，总操作数为 $j-i$。

由此我们可以得到，只要 $a_{i} \ne b_{i}$，都只需要找到 $a$ 中 $i$ 后面第一个 $1$（令它为 $a_{j}$），操作数为 $j-i$。

贪心是需要**证明**的：由于本题中操作仅为取反，所以操作顺序是不会影响结果的，贪心是正确的。

## 解题方法
从头扫到尾，遇到 $a_{i} \ne b_{i}$ 就找到它后面的第一个 $1$（令它为 $a_{j}$），但这样会超出时间限制，可以从上一次找到的 $1$（令它为 $a_{k}$）后面开始找（$(i+1,k+1)_{\max}$），答案加上 $i-j$，把 $a_{j}$ 改为 $0$。
## AC代码

```cpp
#include<bits/stdc++.h>
using namespace std;
string a,b;
long long int l,m,n;
int main(){
	ios::sync_with_stdio(0);
	cin>>n>>a>>b;
	for(long long int i=0;i<n;i++){
		if(a[i]==b[i]) continue;
		l=max(i+1,l);
		while(l<n&&a[l]==48) l++;
		if(l==n){
			cout<<-1;
			return 0;
		}
		m+=l-i;
		a[l++]=48;
	}
	cout<<m;
	return 0;
}
```

---

## 作者：hellolin (赞：1)

[题面(洛谷)](https://www.luogu.com.cn/problem/AT_agc049_b)

[题面(AtCoder)](https://atcoder.jp/contests/agc049/tasks/agc049_b)

AtCoder Problems 评级难度：$\texttt{\color{#72ff72}{1171}}$。

## 题意

- 一个 $N$ 长度的 01 串 $S$，你可以进行若干次如下操作：
   - 选一个不在首位的 $1$ 位，反转这一位和前一位。
- 问有没有可能将 $S$ 变为 $T$，输出 `-1` 或最小次数。

## 思路

这个操作可以看作是将第 $i(2\le i\le N,\ S_i=1)$ 向左移一位（左移到的值做异或）。

开一个 $a$ 队列记录 $T$ 中 $1$ 的位置。再开一个 $b$ 队列，用处下面会提到。

若 $S$ 出现了 $1$，代表这个 $1$ 要去“执行任务”了，分两种情况（当前下标记作 $i(1\le i\le N)$）：

1. $a$ 队列空，代表之前的 $1$ 均已满足情况，再分两种情况：
   1. $b$ 队列空，代表这之前的子串都满足情况，唯有此位不满足（因为 $T$ 的这个位置不是 $1$），将此位入 $b$ 队列。
   2. $b$ 队列非空，代表这之前存在一个 $j(1\le j< i,\ S_j=1,\ T_j=0)$，此时需要将这个 $j$ 位从 $1$ 换为 $0$，记录步骤数，再将此位弹出 $b$ 队列。
2. $a$ 队列非空，代表这之前存在一个 $j(1\le j< i,\ S_j=0,\ T_j=1)$，此时需要将这个 $j$ 位从 $0$ 换到 $1$，记录步骤数，再将此位弹出 $a$ 队列。

**注意 $S$ 与 $T$ 要同时进行操作！否则队列记录的将不是之前的、最近的不同位！**

完成操作后，若 $a$ 或 $b$ 非空，代表操作完成后仍然至少存在一个 $i(1\le i\le N,\ S_i\not =T_i)$。无解，输出 `-1`。

否则，输出记录的步骤。

## 代码

``` cpp
#include <bits/stdc++.h>
using namespace std;
int n;
string s,t;
queue<int>a,b;
long long ans;
int main()
{
    ios::sync_with_stdio(false);
    cin.tie(0);
    cin>>n>>s>>t;
    for(int i=0; i<n; i++)
    {
        if(t[i]=='1')a.push(i);
        if(s[i]=='1')
        {
            if(a.empty())
            {
                if(b.empty()) b.push(i);
                else
                {
                    ans+=i-b.front(); // 记录步骤数
                    b.pop();
                }
            }
            else
            {
                ans+=i-a.front(); // 记录步骤数
                a.pop();
            }
        }
    }
    if(a.size()||b.size())cout<<-1<<endl;
    else cout<<ans<<endl;
    return 0;
}
```

---

## 作者：JAMES__KING (赞：1)

在打模拟赛的时候碰到了这道题，现在来回忆一下自己与众不同的思路。

首先，考虑到要让两个**长度相同**的串变得相同，我们可以按长度逐位循环枚举，而枚举到每一位则会有两种情况：

- $s_i = t_i$ 此时我们可以直接跳过这一位的判断。

- $s_i \ne t_i$ 在这种情况下。我们想：因为只有通过串里的 $1$ 才可以向前一路改变下去。所以，我们可以找到该位之后的第一个 $1$ 位，然后一路向前改变下去。由于是第一个，所以不会出现将两个 $1$ 同时改变的情况。可以证明，这种方法是准确无误的。再进行模拟，如果第一个 $1$ 位的下标为 $x$，那么改变后 $s_x$ 将等于 $0$，而 $s_i$ 将等于 $t_i$。

注意：

1. 不开 long long 见祖宗。

1. 需要一个值来记录上一个 $1$ 出现位置的下标，下一次枚举时只要从后一位开始就行了。

下面贴出代码：

```cpp
#include<bits/stdc++.h>
using namespace std;
int n,s,ss;
long long ans;
char s1[500005],s2[500005];
signed main()
{
   cin>>n;
   cin>>s1>>s2;
   for(int i=0;i<n;i++)
   {
      if(s1[i]==s2[i]) continue;
      s=0;
      for(int j=max(i+1,ss);j<n;j++)//寻找
         if(s1[j]=='1')
         {
            s=j;
            break;
         }
      ss=s+1;
      if(s==0)
      {
         cout<<-1;
         return 0;
      }
      ans+=s-i;
      s1[s]='0';
      s1[i]=s2[i];//改变
   }
   cout<<ans;
   return 0;
}
```


---

## 作者：SilverLi (赞：1)

[Flip Digits の 传送门](https://www.luogu.com.cn/problem/AT_agc049_b)

只有两种情况。

1. $01$->$10$。
2. $11$->$00$。

$001$->$010$->$100$，因此情况 1 可以看作是将 `1` 左移。

从左到右遍历,那么当 $s_i\ne t_i$ 时，只能通过修改 $s_{i+1}$，翻转 $s_i$ 来改变 $s_i$，如果 $s_{i+1}$ 不为 $1$，就需要找到 $s_i$ 右边第一个的 $1$，通过情况 1 把 $1$ 传递到 $s_{i+1}$，因此这题只需要存一下所有 $1$ 的位置，然后从左到右遍历,模拟操作即可。

最后提醒一句，要开 `long long`。

```cpp
#include <bits/stdc++.h>
using namespace std;
#define int long long
const int maxm=2e6+5;
char s[maxm];
char t[maxm];
int n;
signed main(){
    cin>>n;
    cin>>(s+1);
    cin>>(t+1);
    vector<int>pos;
    for(int i=1;i<=n;i++){
        s[i]-='0',t[i]-='0';
        if(s[i])pos.push_back(i);
    }
    int len=pos.size();
    int cur=0;
    int ans=0;
    for(int i=1;i<=n;i++){
        while(cur<len&&pos[cur]<=i)cur++;
        if(s[i]==t[i])continue;
        if(cur>=len){
            cout<<-1<<endl;
            return 0;
        }
        ans+=pos[cur]-i;
        s[pos[cur]]=0;
        cur++;
    }
    cout<<ans<<endl;
    return 0;
}
```

---

## 作者：guoxinda (赞：0)

## 思路：
考虑贪心。在局部上，两位只有数字相同/相反两种情况。
### 数字相同（$11\to00$）
当发现 $1$ 时，只需要找到距离最近的第二个 $1$。\
此时，两个 $1$ 这一段的距离形如 $10\cdots01$。我们要将第 $2$ 个 $1$ 一直和前面的数取反（向左移），总次数加上进行这两个坐标的差。 
### 数字不相同（$01\to10$）
同上，总次数加上坐标的差。
## code 
```cpp 
#include<bits/stdc++.h>
using namespace std;
string s,t;
long long n,ans,j=0;
int main(){
	cin>>n>>s>>t;
	for(int i=0;i<n;i++){
		if(s[i]!=t[i]){//要交换 
			if(j<i+1)j=i+1;//以前搜过的不用再搜了（记忆化） 
			while(j<n&&s[j]=='0')j++;//找到最近的1
			if(j==n){//没找到 
				cout<<-1;
				return 0;
			} 
			s[j]='0';//移到前面了 
			ans+=j-i;
		}
	}
	cout<<ans;
	return 0;
}
```

---

## 作者：I_Like_Play_Genshin (赞：0)

小清新双指针题目

## Solution

记录两个指针，$i, j$ 分别记录现在到了 $T,S$ 的第 $i, j$ 位，那么循环枚举 $i$，对于每一个 $T_i$ 为 $1$ 并且 $T_i \not = S_j$，那么往后枚举 $j$，如果 $S_j$ 为 $1$ 那么交换过来，即答案加上 $|j-i|$，如果 $j$ 大于了 $n$ 还找不到 $1$，那么输出 `-1`。易证，此贪心正确。复杂度为 $O(n)$，可以过掉此题，注意要开 `long long`。

---

## 作者：1zhangziheng2023 (赞：0)

### [题目传送门](https://www.luogu.com.cn/problem/AT_agc049_b)
### 题意
给定一个长度为 $n$ 的01串 $S$，现有一种操作：

- 取一个 $i(1 < i \le n)$ 使 $a_i = 1$，将 $a_i,a_{i-1}$ 进行取反操作。

问是否可以通过若干次操作使得 $S=T$，若可以，输出最小操作次数。
### 思路
数据范围 $1 \le n \le 10^5$，暴力绝对 T 的死死的，
这个时候，我们就可以考虑贪心。为了使操作有意义，每次操作都要为了使 $a_i \ne b_i$ 变为 $a_i = b_i$。

**先分析一下操作：**

既然要使操作的位置 $i$ 满足 $a_i = 1$，且字符串 $S$ 是一个 01 串，所以无非分 2 种情况。

1.`01` -> `10`

2.`11` -> `00`

转换为下列两种情况：

1.即 $a_i = 0$ 且 $b_i = 1$。为了完成此操作，我们要找到 $i$ 右侧的第 $1$ 个 1（设其在第 $j$ 位），从第 $j$ 位到第 $i+1$ 位依次进行操作，也就是将找到的 $1$ 向前传到第 $i$ 位，使其变为 `10`。

总计进行了 $j-(i+1-1)=j-i$ 次操作。

2.即 $a_i = 1$ 且 $b_i = 0$。同上找到 $j$，先从第 $j$ 位到第 $i+2$ 位依次进行操作，将 $1$ 向前传到第 $i+1$ 位，使其变为 `11`，再在 $i+1$ 位进行 1 次操作，使 `11` 变为 `00`。

总计进行了 $j-(i+2-1)+1=j-i$ 次操作。

通过上述分析可得：当 $a_i \ne b_i$ 时，答案 $ans$ 加上 $j-i$，并将 $a_j$ 改为 $0$。

### 超短代码
```cpp
#include<bits/stdc++.h>
using namespace std;
#define int long long
int n,j,ans;
string a,b;
signed main(){
	cin>>n;
	cin>>a>>b;
	for(int i=0;i<n;i++){
		if(a[i]==b[i])continue;
		j=max(j,i+1);
		while(a[j]=='0'&&j<n)j++;
		if(j==n){
			cout<<-1;
			return 0;
		}
		ans+=j-i;
		a[j]='0';
	}
	cout<<ans;
	return 0;
}
```
~~码量最少的一次。~~
### 后记
此题只需仔细分析，得出结论，敲出代码就很轻松了。

此题解部分思路借鉴了 @a18981826590 大神的题解。

若有错误或缺点，欢迎各位 dalao 批评指出。

---

