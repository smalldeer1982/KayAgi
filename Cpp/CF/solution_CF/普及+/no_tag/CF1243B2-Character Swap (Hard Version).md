# Character Swap (Hard Version)

## 题目描述

This problem is different from the easy version. In this version Ujan makes at most $ 2n $ swaps. In addition, $ k \le 1000, n \le 50 $ and it is necessary to print swaps themselves. You can hack this problem if you solve it. But you can hack the previous problem only if you solve both problems.

After struggling and failing many times, Ujan decided to try to clean up his house again. He decided to get his strings in order first.

Ujan has two distinct strings $ s $ and $ t $ of length $ n $ consisting of only of lowercase English characters. He wants to make them equal. Since Ujan is lazy, he will perform the following operation at most $ 2n $ times: he takes two positions $ i $ and $ j $ ( $ 1 \le i,j \le n $ , the values $ i $ and $ j $ can be equal or different), and swaps the characters $ s_i $ and $ t_j $ .

Ujan's goal is to make the strings $ s $ and $ t $ equal. He does not need to minimize the number of performed operations: any sequence of operations of length $ 2n $ or shorter is suitable.

## 样例 #1

### 输入

```
4
5
souse
houhe
3
cat
dog
2
aa
az
3
abc
bca
```

### 输出

```
Yes
1
1 4
No
No
Yes
3
1 2
3 1
2 3
```

# 题解

## 作者：dd_d (赞：2)

[更好的阅读体验](https://www.cnblogs.com/dd-d/p/15342018.html)
### Sol  
首先考虑无解的情况。  
若一个字母在两个串中的出现次数为奇数，一定无解。  
记 $i$ 表示当前枚举到第 $i$ 位。再枚举一个 $j$ 起中转作用。  
分三种情况讨论。  

- $s_i=t_i$，满足条件，枚举下一位即可。  
- $s_i=s_j$，将 $s_j$ 与 $t_i$ 交换即可。  
- $s_i=t_j$，先将 $s_j$ 与 $t_j$ 交换，再将 $s_j$ 与 $t_i$ 交换即可。  

时间复杂度 $O(n^2)$  
### Code  
```cpp  
//LYC_music yyds!
#include<bits/stdc++.h>
#define IOS ios::sync_with_stdio(0)
#define lowbit(x) (x&(-x))
using namespace std;
int read()
{
	int pos=1,num=0;
	char ch=getchar();
	while (!isdigit(ch))
	{
		if (ch=='-') pos=-1;
		ch=getchar();
	}
	while (isdigit(ch))
	{
		num=num*10+(int)(ch-'0');
		ch=getchar();
	}
	return pos*num;
}
void write(int x)
{
	if (x<0)
	{
		putchar('-');
		write(-x);
		return;
	}
	if (x>=10) write(x/10);
	putchar(x%10+'0');
}
void writesp(int x)
{
	write(x);
	putchar(' ');
}
void writeln(int x)
{
	write(x);
	putchar('\n');
}
int n,cnt[26];
vector<pair<int,int> > ans;
char S[101],T[101];
void solve()
{
	n=read();
	memset(cnt,0,sizeof(cnt));
	scanf("%s""%s",S+1,T+1);
	for (int i=1;i<=n;i++)
		cnt[S[i]-'a']++,cnt[T[i]-'a']++;
	for (int i=0;i<26;i++)
		if (cnt[i]&1) 
		{
			puts("No");
			return;
		}
	ans.clear();
	for (int i=1;i<=n;i++)
	{
		if (S[i]==T[i]) continue;
		for (int j=i+1;j<=n;j++)
		{
			if (S[i]==S[j])
			{
				ans.push_back({j,i});
				swap(S[j],T[i]);
				break;
			}
			if (S[i]==T[j])
			{
				ans.push_back({j,j});
				swap(S[j],T[j]);
				ans.push_back({j,i});
				swap(S[j],T[i]);
				break;
			}
		}
	}
	puts("Yes");
	writeln(ans.size());
	for (auto now:ans)
		writesp(now.first),writeln(now.second);
}
signed main()
{
	int T=read();
	while (T--) solve();
}



```

---

## 作者：Rex01 (赞：0)

## [CF1243B2 题目传送门](https://www.luogu.com.cn/problem/CF1243B2)

## 题目大意
给你两个长度为 $n$ 的只包含小写字母的字符串 $S$ 和 $T$。最多进行 $2n$ 次操作，每次选择两个数 $i,j$，其中 $1 \leq i,j \leq n$，交换 $S_i,T_j$。问能否使得 S 和 T 两个串完全相同。

## 解决思路
可以想到**贪心**。首先循环枚举两个串，直到发现某一位不同，再找**从前往后**第一个可以替换的字符，注意这里**不是**找与该字符**位置相同**的字符，而是第一个与 $S$ 串该位置**字符相同**的字符。经过简单分析可得出两种情况：
- 可以替换的字符在 $S$ 串内，直接替换即可；
- 可以替换的字符不在 $S$ 串内，要先把该字符换到 $S$ 串中，然后再替换。

最终看出最多的替换次数为 $2 \times n$ 次，因此只需判断替换后是否可以相等即可。

### 注意事项
> 最终看出最多的替换次数为 $2 \times n$ 次，因此只需判断替换后是否可以相等即可。

因此数组要开 $2 \times n$ 的大小。

## 代码展示
```cpp
#include <iostream>
#include <algorithm>
//拒绝万能头，从我做起
using namespace std;

const int N = 60; 
int k, n, ans[110][2];
char s[N], t[N];

int main()
{
    cin >> k;
    while(k--)
    {
        cin >> n >> s >> t;
        int cnt = 0;
        bool f1 = true;
        for(int i = 0; i < n; i++)
        {
            if(s[i] != t[i])
            {
                bool f2 = false;
                for(int j = i + 1; j < n; j++)
                {
                    if(s[i] == s[j])
                    {
                        ans[++cnt][0] = j;
                        ans[cnt][1] = i;
                        swap(s[j], t[i]);
                        f2 = true;
                        break;
                    }
                    if(s[i] == t[j])
                    {
                        ans[++cnt][0] = j;
                        ans[cnt][1] = j;
                        swap(s[j], t[j]);
                        ans[++cnt][0] = j;
                        ans[cnt][1] = i;
                        swap(s[j], t[i]);
                        f2 = true;
                        break;
                    }
                }
                if(!f2)
                {
                    f1 = false;
                    break;
                }
            }
        }
        if(!f1) cout << "No" << endl;
        else
		{
			cout << "Yes" << endl << cnt << endl;
            for(int i = 1; i <= cnt; i++)
            	cout << ans[i][0] + 1 << " " << ans[i][1] + 1 << endl;
        }
    }
    return 0;
}
```

---

## 作者：FiraCode (赞：0)

## 题解思路：
我们先扫描一遍 $s$ 和 $t$，然后如果啊 $s_{i} != t_{i}$，那么在 $t$ 中找到一个 $t_{j}$ 使得 $t_{j} == t_{i}$ 然后交换一下 $t_{j}$ 和 $s_{i}$。

我们看一下样例：

`souse` 和 `houhe`

它们按照上述法方只需要 $1$ 次就可以了。这是一种情况。

在看一个：

`abc` 和 `bca`

我们发现他第一个就不相等了，但 `bca` 里没有 $\ge 2$ 个 `b`，但我们可以：
![](https://cdn.luogu.com.cn/upload/image_hosting/02va8ppr.png)

那么我们就可以把他首字母变成相等，一共用了 $2$ 步。

那我们就可以分两种情况来贪心：
*   1 若他们有一位不相等，并第二个串里有一个与他相等的字母，那么次数加 $1$。
*   2 若他们有一位不相等，而第二串里没有与他相等的字母，但第一个串里有一个跟第二个串里的字母相等的，答案加 $2$。

因为他至多每次都是情况 $2$，那么最多就执行 $n$ 次，所以执行次数一定 $\le 2n$。

## AC CODE:
```cpp
#include <iostream>
#include <algorithm>
#include <cstdio>
#include <cstring>
#include <vector>
using namespace std;
int n;
string s , t;
vector <pair <int , int>> op;
void solve () {
    op.clear();
    scanf ("%d" , &n);
    cin >> s >> t;
	for (int i = 0; i < s.size(); ++ i) {
		if (s[i] != t[i]) {//若他们不相等 
			int flag = 0;
			for (int j = i + 1; j < t.size(); ++ j)
				if (t[j] == t[i]) {//若有与他相等的 
					flag = 1;//代表已经让s[i] == t[i]了 
					op.push_back ({i + 1 , j + 1});//把操作加入到vector里 
					swap (s[i] , t[j]);//交换 
					break;
				} 
			if (flag == 0) {//若t串里没有与t[i]相等的则尝试方案二 
				for (int j = i + 1; j < s.size(); ++ j)
					if (s[j] == t[i]) {//第二种情况 
						flag = 1;
						op.push_back ({j + 1 , t.size()});//按照第二个情况进行操作 
						swap (s[j] , t[t.size() - 1]);
						op.push_back ({i + 1 , t.size()});
						swap (s[i] , t[t.size() - 1]);
					}
			}
			if (!flag) {//如果这两种情况都不行，那么就无解 
				puts("NO");
				return ; 
			} 
		}
	}
	puts("YES");
	cout << op.size() << endl;//一共有多少次操作，vector有一个好处就是可以自己通过size来知道他的长度，而数组就得用一个变量来储存。
	for (int i = 0; i < op.size(); ++ i) 
		cout << op[i].first << ' ' << op[i].second << endl;
}
int main() {
    int T;
    scanf ("%d" , &T);
    while (T --)
    	solve();
    return 0;
}
```

---

## 作者：lsr1409111459 (赞：0)

#### 1 题目描述（[传送门](https://www.luogu.com.cn/problem/CF1243B2)）

##### 1.1 题目大意

你有两个只由小写字母组成的字符串 $s$ 和 $t$ ，要求你每次交换两者的一个字符，在最多 $2n$ 次交换后使得两者相同。

注意我们只需让两者相同，但不需最小化交换次数，即任何的小于等于 $2n$ 次操作使得两者相同都是满足题意的。

##### 1.2 输入格式

第一行一个整数 $k(1\leq k \leq 1000)$ ，表示问题组数。

对于每组问题，共三行。

每组第一行为一个整数 $n(2 \leq n \leq 50)$ ，表示 $s$ 和 $t$ 的长度。

每组第二行为一个由小写字母组成的长度为 $n$ 的字符串 $s$ 。

每组第三行为一个由小写字母组成的长度为 $n$ 的字符串 $t$ 。

##### 1.3 输出格式

共 $k$ 行。

对于每组问题，如果不能在最多 $2n$ 次交换后使其相等，输出一行 ``NO`` 即可。

反之，输出三行，第一行为 ``YES`` 。第二行为你的操作数 $x(x \leq 2n)$ 。

接下来 $x$ 行为你的 $x$ 次操作，每行两个整数，分别为要交换的 $s$ 和  $t$ 中的字符的位置。

#### 2 解题思路

贪心。我们枚举两个串，如果某一位不同，则向后寻找第一个可以替换的字符（第一个与 $s$ 串该位置字符相同的字符）。因为只能在两个串之间互相交换而不能串内交换，所以又分为两种情况：

case1： ``souse`` 和 ``houhe`` ，我们执行操作 $4,1$ 即可。

case2： ``souhe`` 和 ``house`` ，我们执行 $4,4$ ，再执行 $4,1$ 。

由此我们可以看出，如果可以替换的字符在 $s$ 串内，直接替换即可，否则，要先把该字符换到 $s$ 串中，然后再替换。

最后可以看出，我们最多替换的次数为 $2n$ 次，因此只需判断替换后是否可以相等即可。

#### 3 解题代码

```cpp
#include <iostream>
#include <algorithm>
using namespace std;
int k,n;
char s[60];
char t[60];
int ans[110][2],cnt;
int main()
{
    scanf("%d",&k);
    while(k--)
    {
        scanf("%d%s%s",&n,s,t);
        cnt=0;
        bool f=true;
        for(int i=0;i<n;i++)
        {
            if(s[i]!=t[i])
            {
                bool flag=false;
                for(int j=i+1;j<n;j++)
                {
                    if(s[i]==s[j])//case 1
                    {
                        ans[++cnt][0]=j;
                        ans[cnt][1]=i;
                        swap(s[j],t[i]);
                        flag=true;
                        break;
                    }
                    if(s[i]==t[j])//case 2
                    {
                        ans[++cnt][0]=j;
                        ans[cnt][1]=j;
                        swap(s[j],t[j]);
                        ans[++cnt][0]=j;
                        ans[cnt][1]=i;
                        swap(s[j],t[i]);
                        flag=true;
                        break;
                    }
                }
                if(!flag)//如果找不到，则为NO
                {
                    f=false;
                    break;
                }
            }
        }
        if(!f)printf("NO\n");
        else{
            printf("YES\n%d\n",cnt);
            for(int i=1;i<=cnt;i++)
                printf("%d %d\n",ans[i][0]+1,ans[i][1]+1);
        }
    }
    return 0;
}
```

#### 4 解题心得

贪心策略还比较好想，但是考场上因为没有意识到题目难度非递增这点所以，这题看了眼样例就直接过了也没回来看，后来看榜才发现榜前的就我没写这道题……最后就是，要注意答案数组开 $2n$ ，脑残没开又WA一次。

---

