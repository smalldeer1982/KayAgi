# Not a Cheap String

## 题目描述

Let $ s $ be a string of lowercase Latin letters. Its price is the sum of the indices of letters (an integer between 1 and 26) that are included in it. For example, the price of the string abca is $ 1+2+3+1=7 $ .

The string $ w $ and the integer $ p $ are given. Remove the minimal number of letters from $ w $ so that its price becomes less than or equal to $ p $ and print the resulting string. Note that the resulting string may be empty. You can delete arbitrary letters, they do not have to go in a row. If the price of a given string $ w $ is less than or equal to $ p $ , then nothing needs to be deleted and $ w $ must be output.

Note that when you delete a letter from $ w $ , the order of the remaining letters is preserved. For example, if you delete the letter e from the string test, you get tst.

## 样例 #1

### 输入

```
5
abca
2
abca
6
codeforces
1
codeforces
10
codeforces
100```

### 输出

```
aa
abc

cdc
codeforces```

# 题解

## 作者：Halberd_Cease (赞：1)

其它大佬把翻译说得很清楚了，我就不再赘述了。

很显然，这是一道贪心题，要让保留的字符最多，那么每个字符的价值就要最少。

贪心策略：

1. 将字符串按升序排序；

2. 从前往后依次枚举价值和，如果超过直接退出，否则将该位原位标记为选中，继续枚举；

3. 从头遍历原字符串，如果标记就输出。

注意，如果要求的最大价值比价值总和大就输出全部字符串然后 ```continue```。

Code:

```cpp
#include<bits/stdc++.h>
using namespace std;
struct Node{
	char x;
	int id;
	bool can;
}a[200010];
char str[200010];
bool can[200010];
bool cmp1(Node x,Node y)
{
	return x.x<y.x;
}
bool cmp2(Node x,Node y)
{
	return x.id<y.id;
}
main()
{
	ios::sync_with_stdio(0);
	cin.tie(0);
	cout.tie(0);
	int t;
	cin>>t;
	while(t--)
	{
		int total=0;
		memset(str,0,sizeof(str));
		memset(a,0,sizeof(a));
		memset(can,0,sizeof(can));
		int maxn;
		cin>>str;
		int len=strlen(str);
		for(int i=0;i<len;i++)
		{
			a[i].x=str[i];
			a[i].id=i;
			total+=a[i].x-'a'+1;
		}
		cin>>maxn;
		if(maxn>=total)
		{
			cout<<str<<'\n';
			continue;
		}
		sort(a,a+len,cmp1);
		total=0;
		for(int i=0;i<len;i++)
		{
			if(total+a[i].x-'a'+1<=maxn)
			{
				total+=(a[i].x-'a'+1);
				a[i].can=1;
			}
			else
			break;
		}
		for(int i=0;i<len;i++)
		{
			if(a[i].can)can[a[i].id]=1;
		}
		for(int i=0;i<len;i++)
		{
			if(can[i])cout<<str[i];
		}
		cout<<'\n';
	}
 } 
```

---

## 作者：NATO (赞：1)

### 题目翻译：
$s$ 是一串小写的拉丁字母。它的价格是它包含的字母的指数（$1$ 到 $26$ 之间的整数）的和。例如，字符串 ```abca``` 的价格是 $1+2+3+1=7$ 给定了字符串 $w$ 和整数 $p$。从 $w$ 中删除最小数量的字母，使其价格小于或等于 $p$，并打印结果字符串。注意，结果字符串可能是空的。你可以任意删除字母，它们不必连在一起。如果给定字符串 $w$ 的价格小于或等于 $p$，那么不需要删除任何内容，$w$ 必须输出。注意，当您从 $w$ 中删除一个字母时，将保留其余字母的顺序。例如，如果您从字符串 ```test``` 中删除字母 ```e```，您将得到 ```tst```。

### 题目分析：

为了使剩下字符尽量少，因此就要使删除字符在数量最少的情况下价格最多，因此采用贪心，将所有字符从大到小排序后从大到小删除字符到总价格小于等于 $p$ 时输出即可。

因为本题带有特殊评测，因此只要是输出字符串包含字符数与顺序对（排序时记录原编号，删除时标记删除原编号字符）即可。

#### 参考代码：
```cpp
#include<bits/stdc++.h>
#define ll long long
using namespace std;
ll t;
string a;
struct px
{
	ll a;
	ll id;
}st[200005];
ll p,cnt,sum,len,op;
bool vis[200005];
bool cmp(px ak,px b)
{
	return b.a<ak.a;
}
int main()
{
	ios::sync_with_stdio(0);
	cin>>t;
	while(t--)
	{
		cin>>a>>p;
		cnt=0;
		sum=0;
		op=0;
		len=a.size();
		for(ll i=0;i<len;++i)
			cnt+=1+a[i]-'a',vis[i]=0,st[++sum].a=a[i]-'a'+1,st[sum].id=i;
		if(cnt<=p)
		{
			cout<<a<<endl;continue;
			}	
		sort(st+1,st+1+sum,cmp);
		while(1)
		{
			vis[st[++op].id]=1;
			cnt-=st[op].a;
			if(cnt<=p||op==sum)//如果已经删除完了所有字符，也要记得退出！！！
				break;
		}
		for(ll i=0;i<len;++i)
			if(!vis[i])
				cout<<a[i];
		cout<<'\n';
	}
}
```


---

## 作者：tzyt (赞：1)

题目链接[（CF](https://codeforces.com/problemset/problem/1702/D)，[洛谷）](https://www.luogu.com.cn/problem/CF1702D) | 强烈推荐[博客](https://ttzytt.com/2022/07/CF1702/)中观看。

## 题意：
设 $s$ 为一个由小写拉丁字母组成的字符串。它的价格被定义为，字符串中每个字母在字母表中的位置的和。

比如，字符串 $\texttt{abca}$ 的价格是 $1 + 2 + 3 + 1 = 7$。

现在给你一个字符串 $w (|w| \le 2\cdot 10^5)$，和一个整数 $p$，请你从字符串中**尽量少**的移除字母，使得 $w$ 的价格小于或等于 $p (1 \le p \le 5\ 200\ 000)$。注意移除的字母数量可以是 $0$ 个，也可以是字符串中全部的字母。

## 思路：
这道题的难度其实跟上一个差不多。因为题目让你删除尽量少的字母，所以我们直接挑对价格贡献大的字母删，直到整个字符串的价格小于等于 $p$。

具体的实现上，我们还是可以用 `map` 建立一个字符到出现次数的映射（或者说桶）。

然后我们倒着遍历这个 `map`，这样先遍历到的字符就对价格有更大的贡献。然后在遍历时如果发现当前的价格大于 $p$，就删除这个字符。并且如果我们删除了这个字符，那也相应的给字符的出现次数 $-1$。

最后输出时，我们遍历原来的字符串，如果发现对应的字符在桶里有出现，就输出，然后把出现次数 $-1$，否则就不输出了。

## 代码：
```cpp
// author: ttzytt (ttzytt.com)
#include <bits/stdc++.h>
using namespace std;
#define ll long long
int main() {
    int t;
    cin >> t;
    while (t--) {
        string str;
        int p;
        cin >> str >> p;
        map<char, int> bkt; // 桶
        ll price = 0;
        for (char ch : str) {
            bkt[ch]++;
            price += (ch - 'a' + 1);
            //计算初始价格
        }
        map<char, int>::reverse_iterator it = bkt.rbegin();
        //倒着遍历 map，所以需要用反向迭代器
        while (price > p) {
            // 如果价格没有小于等于 p，就一直删
            (*it).second--; 
            // 减少桶代表的出现次数
            price -= ((*it).first - 'a' + 1);
            // 维护价格
            if ((*it).second <= 0) {
                // 如果说这个字母已经被删光了
                if (it != bkt.rend()) it++;
                // 并且这不是字符串中最小的字符
                // 我们就开始删比当前字符小的字符
            }
        }
        string ans;
        for (char ch : str) {
            if (bkt[ch] > 0) {
                //如果发现这个字符还没被删除
                ans.push_back(ch);
                bkt[ch]--;
            }
        }
        cout << ans << endl;
    }
}
```
最后，希望这篇题解对你有帮助，如果有问题可以通过评论区或者私信联系我。

---

## 作者：yeshubo_qwq (赞：1)

## Description

字母 a 的价值为 $1$，字母 b 的价值为 $2$，以此类推，字母 z 的价值为 $26$。

给定一个字符串，要求删除最少的字母，使该字符串的价值不超过 $p$。

## Solution

贪心，想让删除的字母最少，就让删除字母的价值最大。

优先删除价值大的字母，用井号标记，并减去对应价值。

当剩余价值不超过 $p$ 时，输出剩下的字母，注意不要输出井号。

## Code

```cpp
#include <bits/stdc++.h>
//#define int long long
using namespace std;
char s[200005],c;
int p,n,res,i,j;
void solve(){
	cin>>s+1>>p,n=strlen(s+1);
	res=0;
	for (i=1;i<=n;i++) res+=(s[i]&31);
	if (res<=p) {cout<<s+1<<'\n';return;}
	for (c='z';c>='a';c--){
		for (i=1;i<=n;i++)
			if (s[i]==c){
				res-=(c&31);
				s[i]='#';
				if (res<=p) {
					for (j=1;j<=n;j++)
						if (s[j]!='#') cout<<s[j];
					cout<<'\n';
					return;
				}
			}
	}
}
signed main(){
	ios::sync_with_stdio(0),cin.tie(0),cout.tie(0);
	int tests=1;
	cin>>tests;
	while (tests--)
		solve();
	return 0;
}

```


---

## 作者：HarunluoON (赞：0)

## 题意简述

定义一个完全由小写英文字母组成的字符串的“价值”（price）为每个字符在英文字母表中的出现顺序之和，如 $\tt{abca}$ 的价值为 $1+2+3+1=7$。

有 $t$ 个测试用例，每个测试用例中，给你一个完全由小写英文字母组成的字符串 $w$ 和一个正整数 $p$，要求在 $w$ 中删去最少的字符，使它的价值小于等于 $p$。你需要输出删除字符后的 $w$ 的一种可能的情况。

## 分析

因为只要求删除字符后 $w$ 的价值小于等于 $p$，显然删除字母表中出现位置越靠后的字符，$w$ 的价值减小得越快。这样，我们就可以通过删除更少的字符而使得价值更小了。

## 部分代码

```cpp
char w[200001],ww[200001];//w 数组是输入和输出的数组，ww 数组是 w 的副本
int del[27];//del 数组表示每个字符需要被删除多少次
bool comp(char x,char y)
{
	return x>y;//按字符 ASCII 码值从大到小排序
}
int size(char str[])//求 char 数组的长度
{
	int sz=0;
	for(int i=0;i<200001;i++)
	{
		if(str[i]>='a'&&str[i]<='z')
		sz++;
		else
		break;
	}
	return sz;
}
int price(char str[])//求 char 数组的价值
{
	int res=0;
	for(int i=0;i<200001;i++)
	{
		if(str[i]>='a'&&str[i]<='z')
		res+=(str[i]-'a'+1);
		else
		break;
	}
	return res;
}
void work()
{
	int p,wwpr,pos=0,sizew;//wwpr 是当前 ww 的价值
	memset(w,0,sizeof(w)),memset(ww,0,sizeof(ww)),memset(del,0,sizeof(del));//数组初始化
	scanf("%s",w);
	sizew=size(w);//求 w 的长度
	cin>>p;
	for(int i=0;i<sizew;i++)//复制 w 到 ww
	{
		if(w[i]>='a'&&w[i]<='z')
		ww[i]=w[i];
		else
		break;
	}
	wwpr=price(w);
	sort(ww,ww+sizew,comp);//将 ww 按字符在字母表中出现位置从后到前排序
	while(wwpr>p)
	{
		del[(ww[pos]-'a'+1)]++;//决定哪些字符会被删除
		wwpr-=(ww[pos]-'a'+1);
		pos++;
	}
	for(int i=0;i<sizew;i++)
	{
		if(del[(w[i]-'a'+1)]>0)//如果这个字符需要被删除，则不输出它
		{
			del[(w[i]-'a'+1)]--;
			continue;
		}
		else//否则不需要被删除，输出
		printf("%c",w[i]);
	}
	printf("\n");
}
```

---

