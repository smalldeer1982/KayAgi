# Minimum Notation

## 题目描述

You have a string $ s $ consisting of digits from $ 0 $ to $ 9 $ inclusive. You can perform the following operation any (possibly zero) number of times:

- You can choose a position $ i $ and delete a digit $ d $ on the $ i $ -th position. Then insert the digit $ \min{(d + 1, 9)} $ on any position (at the beginning, at the end or in between any two adjacent digits).

What is the lexicographically smallest string you can get by performing these operations?

A string $ a $ is lexicographically smaller than a string $ b $ of the same length if and only if the following holds:

- in the first position where $ a $ and $ b $ differ, the string $ a $ has a smaller digit than the corresponding digit in $ b $ .

## 说明/提示

In the first test case:

- Delete $ 8 $ and insert $ 9 $ at the end of the notation. The resulting notation is $ 04299 $ .
- Delete $ 4 $ and insert $ 5 $ in the $ 3 $ -rd position of the notation. The resulting notation is $ 02599 $ .

Nothing needs to be done in the second and third test cases.

## 样例 #1

### 输入

```
4
04829
9
01
314752277691991```

### 输出

```
02599
9
01
111334567888999```

# 题解

## 作者：win10 (赞：5)

### 题目大意

给定一个仅包含 $0$ 到 $9$ 这几个数字的字符串，你可以执行以下操作任意次：

选择字符串中的一个数字 $d$，将 $d$ 删除后，向字符串任意位置插入一个数字 $\min(d+1,9)$.

求能够得到的字典序最小的字符串。

### Solution

根据题意，我们想要让字典序最小，就要尽可能将小的数放在前面。每次执行一次操作后，我们都会让一个数变大，只有变大后把它放在字符串后面，让一个更小的数能到前面来，他才能更优。

举个例子：

![](https://cdn.luogu.com.cn/upload/image_hosting/ri77npmx.png)

第一个样例中， $2$ 在 $4$ 和 $8$ 的后面，更优的解一定是把它放到前面来，于是我们将前面的 $4$ 和 $8$ 处理后放到后面。

想到了什么？有单调栈的感觉。

具体地说，就是维护一个单调栈，将弹出的元素 $d=\min(d+1,9)$ 全部存入一个 vector 中，将所有元素排序。最后输出答案，在输出单调栈中元素的同时，输出 vector 中与之相等的元素，因为已经排完序了，直接从前向后扫即可。

代码如下：

~~~cpp
#include<bits/stdc++.h>
using namespace std;

inline int read() {
	int x = 0,f = 1;
	char ch = getchar();
	while(ch < '0' || ch > '9') {
		if(ch == '-') f = -1;
		ch = getchar();
	}
	while(ch >= '0' && ch <= '9') {
		x = (x << 1) + (x << 3) + (ch ^ 48);
		ch = getchar();
	}
	return x * f;
}

int T;
string s;
stack<char> st;
vector<char> els,ans;

void work() {
	cin >> s;
	int len = s.length();
	for(int i = 0;i < len;i++) {
		while(!st.empty() && st.top() > s[i]) {
			els.push_back(min(st.top() + 1,57));
			st.pop();
		}
		st.push(s[i]);
	} //单调栈
	while(!st.empty()) {
		ans.push_back(st.top());
		st.pop();
	}
	sort(els.begin(),els.end());
	int pos = 0;
	for(int i = ans.size() - 1;i >= 0;i--) {
		cout << ans[i];
		while(pos < els.size() && els[pos] >= ans[i] && els[pos] <= ans[i-1] && i > 0) cout << els[pos++];
	}
	for(int i = pos;i < els.size();i++) cout << els[i];
	cout << endl;
	return;
}

int main() {
	T = read();
	while(T--) {
		els.clear();
		ans.clear();
		work();
	}
	return 0;
}

~~~

---

## 作者：wangziyang_NORE (赞：2)

#### **题解**

首先我们要明白，如果这个数后面有比他小的数，他就需要移动(+1)。那么用mn记录完他后面最小值后一比，如果和他一样，证明他就是后面最小的，不用动，只挪大的。其实就是贪心和结构体排序。

#### **参考代码**

```cpp
#include<bits/stdc++.h>
using namespace std;
int n,len,a[200005],mn[200005],cnt[14];
char str[200005];
//a[]:将str转存为int后的形式。
//mn[]:这一位后面的最小的数。
int main()
{
	cin>>n;
	while(n--)
	{
		cin>>str;
		len=strlen(str);
		for(int i=0;i<=len;i++)//要将所有mn初始化到最大值（9就可以）。
		{
			mn[i]=9;
		}
		for(int i=0;i<len;i++)
		{
			a[i]=str[i]-'0';//转化。
		}
		for(int i=len-1;i>=0;i--)
		{
			mn[i]=min(mn[i+1],a[i]);//记录从这个数开始后面最小的数。
			if(mn[i]!=a[i])//如果这一位的最小值不等于他本身，证明后面有比它小的，要往后移（+1）。
			{
				a[i]=min(a[i]+1,9);
			}
		}
		for(int i=0;i<len;i++)//把加完一的排序。
		{
			cnt[a[i]]++;
		}
		for(int i=0;i<=9;i++)
		{
			while(cnt[i])
			{
				cout<<i;
				cnt[i]--;
			}
		}
		cout<<endl;
	}
	return 0;
}
```

---

## 作者：GalwayGirl (赞：2)

这是我打过的最难的 Div2，C 题卡了我好久，~~B 题比 C 题还难。~~

## Solution
看完题目，我们很快就能想到一种做法，因为选定了数字后可以任意插入，所以如果前面有数字比后面大，就肯定选定它并丢到后面，保证单调性，这样就是最优的。其实大家肯定都能想到，只不过代码实现自我感觉很恶心。

我们可以先记录每个数字出现的次数，然后从小枚举到大，将它前面比它小的数丢进 vector 里面，别忘记把枚举的数字也丢进去。注意：当前面比它小的数被移动后，需要标记一下，下次不再访问，~~我就卡在这里。~~
最后将 vector 排个序，输出即可。

最后贴上正确代码。
```cpp
#include<bits/stdc++.h>
using namespace std;
int t,cnt[110];
bool vis[210000];
string s;
void solve(){
    cin>>s;
    int sz=s.size();
    for(int i='0';i<='9';i++)cnt[i]=0;
    for(int i=0;i<sz;i++)cnt[s[i]]++,vis[i]=false;
    vector<char>ans;
    for(int i='0';i<='9';i++){
        if(!cnt[i])continue;
        for(int j=0;j<sz;j++){
            if(!cnt[i])break;
            if(vis[j])continue;
            if(s[j]>i){
                cnt[s[j]]--;
                int ls='9';
                ans.push_back(char(min(s[j]+1,ls)));
                vis[j]=true;
            }   
            if(s[j]==i){
                cnt[i]--;vis[j]=true;
                ans.push_back(char(i));
            }
        }
    }
   sort(ans.begin(),ans.end());
   for(int i=0;i<ans.size();i++)cout<<ans[i];
   cout<<endl;
}
int main(){
    scanf("%d",&t);
    while(t--)solve();
    return 0;
}
```


---

## 作者：Vct14 (赞：1)

模拟赛 T1，感觉这题不至于黄吧。

因为要让字典序最小，所以我们要贪心地把较小的数往前放。即一个数要被删除当且仅当它的后面有比它更小的数。我们维护一下后缀最小值并将其和当前数比较即可判断其是否要被删除。由于字典序最小时字符串中的数字一定单调不减，且删除后可以在任意位置插入，所以我们直接将要删除的数加一后排序即可。

```c++
#include<bits/stdc++.h>
using namespace std;

int b[200005];
int mn[200005];

int main(){
	int t;cin>>t;
	while(t--){
		string a;cin>>a;
		int l=a.length();
		b[l-1]=a[l-1]-'0';mn[l-1]=b[l-1];
		for(int i=l-1-1; i>=0; i--){
			b[i]=a[i]-'0';
			mn[i]=min(b[i],mn[i+1]);
			if(b[i]!=mn[i]) b[i]=min(b[i]+1,9);
		}
		sort(b,b+l);
		for(int i=0; i<l; i++) cout<<b[i];cout<<"\n";
	} 
	return 0;
}
```

---

## 作者：CNS_5t0_0r2 (赞：0)

模拟赛刷到这题，挺简单的，写一篇题解。

贪心策略：依次把最大的数排到最后。

严格证明我不会，但是不难想到：先把大数往后排可以让小数在自身不变大的情况下尽可能往前排，肯定不会比先动小数更差。

```cpp
#include<bits/stdc++.h>
using namespace std;
const int N = 2e5 + 9;
int n;
char s[N];
int a[N];
int cnt[10];
int f(int x){
	return min(x + 1,9);
}
int main(){
	ios::sync_with_stdio(false);
	cin.tie(0);cout.tie(0);
	int T;
	cin >> T;
	while(T--){
		memset(cnt,0,sizeof cnt);
		cin >> (s + 1);
		n = strlen(s + 1);
		for(int i = 1;i <= n;i++)
			a[i] = s[i] - '0';
		int Min = 114514;
		for(int i = n;i >= 1;i--){
			cnt[a[i] > Min ? f(a[i]) : a[i]]++;
			Min = min(Min,a[i]);
		}
		for(int i = 0;i <= 9;i++)
			while(cnt[i]--)
				cout << i;
		cout << '\n';
	}
	return 0;
}
```

---

## 作者：Fu_Da_Ying (赞：0)

## [原题链接](https://www.luogu.com.cn/problem/CF1730C)
## 题意：

给定一个仅包含 $0$ 到 $9$ 这几个数字的字符串，进行任意次以下操作：选择字符串中的一个数字 $d$，将 $d$ 删除后，向字符串任意位置插入一个数字 $\min(d+1,9)$。

求能够得到的字典序最小的字符串。

## 思路：

做题先看样例，例如这个的例子：$04829$，不考虑一次操作会让那个数 $+1$ 的情况下，容易想到让字母序最小的方法，肯定是让字母序小的在前，大的在后。

再加入 $+1$ 的限制后，不难想到，让小数向前的字母序，肯定比让大数向后的字母序小。就像上面的例子，
让 $2$ 向前的话，会让 $2$ 加 $1$，让 $4$ 和 $8$ 向后，会让 $4$ 和 $8$ 加 $1$，但明显是后者更好。

这样就有思路了，找出像例子中 $4$ 和 $8$ 那种在比自己小的数前的数，令其 $+1$ 即可。

## Code:
```cpp
#include<bits/stdc++.h>
using namespace std;
long long t,sum,c[200015],b[200015]={-1},xx,j;//j为这个b,c数组的长度
char x;
int main(){
	scanf("%lld\n",&t);
	while(t--){
		j=0;
		for(;;){
			scanf("%c",&x);
		    if(x=='\n'){
			    break;
		    }
		    xx=x-'0';//预处理x
		    sum=j;
		    while(b[sum]>xx||b[sum]==-1){//当x小于前面的数时 
		    	--sum;
		    	if(b[sum+1]==-1){//如果这个大于x的数不在b数组中,则不进行修改操作 
		    		continue;
				}
		    	c[sum+1]=min(1ll*9,c[sum+1]+1);//处理c数组,将大于x的数+1
		    	b[sum+1]=-1;//b数组的那个大于x的数清空,用-1来表示
			}
			++j;
			c[j]=b[j]=xx;//无论结果如何,都将x加入b,c数组 
		}
		sort(1+c,1+j+c);//排序,使这个序列为字典序最小
		for(int i=1;i<=j;i++){
			printf("%lld",c[i]);
		}
		printf("\n");
	}
    return 0;
}
```

### [$AC$ 记录](https://www.luogu.com.cn/record/169519045)

---

## 作者：Erotate (赞：0)

### Solution
显然，我们需要让较小的数不移动，转而去移动较大的数字。

那么，我们用个 vector 来记录每一个数字出现的位置都有哪些，再用个 $sum$ 数组来记录每个数组出现的次数。然后开始从 $0$ 到 $10$ 枚举，如果 $sum_i$ 为 0 的就跳过，否则分类讨论：

1. 如果这个数是最小的数，那就不动它。
2. 否则，我们用一个 $flag$ 来记录上一个处理的数。如果当前这个数所在的位置，在上一个数出现的最后一个位置的前面，那我们就要把它移动到后面去。否则，就保留原位，然后更新一下 $flag$ 即可。

### 代码：
```cpp
#include<bits/stdc++.h>
using namespace std;
const int N=2e5+5;
int t,sum[N],cnt;
char s[N],ans[N];
vector<int>pos[10];
int main(){
	scanf("%d",&t);
	while(t--){
		for(int i=0;i<10;++i) pos[i].clear();
		memset(sum,0,sizeof(sum));
		memset(ans,0,sizeof(ans));
		cnt=0;
		scanf("%s",s+1);
		int n=strlen(s+1),flag=0;
		for(int i=1;i<=n;++i){
			pos[(int)s[i]-'0'].push_back(i);
			sum[(int)s[i]-'0']++;
		}
		for(int i=0;i<=9;++i){
			if(!sum[i]) continue;
			if(!flag){
				for(int j=1;j<=sum[i];++j) ans[++cnt]=(char)(i+'0');
				flag=i+1;
			}else{
				int flag1=0;
				for(int j=pos[i].size()-1;j>=0;--j){
					if(pos[i][j]>pos[flag-1][pos[flag-1].size()-1]){
						ans[++cnt]=(char)(i+'0');
						flag1=1;
					}else ans[++cnt]=min((char)(i+1+'0'),'9');
				} 
				if(flag1) flag=i+1;
			}
		}
		for(int i=1;i<=n;++i) printf("%c",ans[i]);
		puts("");
	}
	return 0;
}
```


---

## 作者：abensyl (赞：0)

原题：[CF1730C Minimum Notation。](https://www.luogu.com.cn/problem/CF1730C)

**update**：对于原题传送门链接错误和部分不清楚的描述进行了修改。

## 思路

在本题中，我们只有一种操作：选择字符串中的一个数 $d$，将 $d$ 删除后，向字符串任意位置插入一个数字 $\min(d+1,9)$。

在最理想化的情况下，我们应该把每一个被移动过的数字直接放到它应该在的地方，这样避免了二次移动导致数字额外增加。

而且，为了使得到的字符串字典序最小，应当保留较小数不变，操使作大数加一。

所以我们只要找到需要移动的数字并对他进行加一即可。

- 什么样的数字需要操作？

> 当一个数的后面有比它小的数时就应当移动，否则保留。

> 但是，要额外注意的是，如果比他小的数已经被移走了，就不要再移动了。

这样，我们便可以轻易得到答案了。

## 代码

```cpp
#include<iostream>
#include<cstring>
#include<vector>
#include<algorithm>
using namespace std;
const int N = 2e5+5;
bool f[N];
void solve() {
	memset(f,0,sizeof f);
  string s;
  cin>>s;
  vector<char> res;
  int op='0';
  int cnt;
  for(int i=0;i<=9;++i) {
  	cnt=0;
		for(int j=s.size()-1;j>=0;--j) {
			if(f[j]) continue;
	  	if(s[j]==op) cnt++,res.push_back(s[j]),f[j]=1;
	  	else if(s[j]>op) {
	  		if(cnt) res.push_back(min(s[j]+1,int('9'))),fuck[j]=1;
			}
		} 
		op++;
  }
  sort(res.begin(),res.end());
  for(auto c:res) cout<<c;
  cout<<'\n';
}
int main() {
  ios::sync_with_stdio(0);
  cin.tie(0);
  cout.tie(0);
  int T;
  cin>>T;
  while(T--) solve();
  return 0;
}
```

[我的 AC 记录。](https://www.luogu.com.cn/record/90115703)

---

## 作者：西湖水妖 (赞：0)

### 题意简述

+ 给定一个只包含 $0$ 到 $9$ 这些数字的字符串 $s$
+ 你可以执行任意次（可以 $0$ 次）下列操作：
  + 选择任意一个字符 $d$，删除它，并将 $\min(d+1,9)$ 插入到字符串任意位置（可以头、尾）。
+ 你需要求出经过操作后字典序最小的字符串。
+ 有 $t$ 组数据，$1\le{t}\le10^4,1\le{|s|}\le2\times10^5$。所有字符串长度总和不超过 $2\times10^5$。

### 题目分析

已知：同上。

求证：最终的答案字符串里的字符单调不递减。

证明：反证法。

假设原命题不成立，即存在答案中第 $i$ 位的字符为 $c$，第 $i+1$ 为的字符为 $d$，$c>d$。

那么，先删除 $c$，再把 $\min(c+1,9)$ 插入到 $d$ 后面。这样，第 $i$ 位的字符由 $c$ 变成了更小的 $d$，并且这之前的字符都没有变化，使得答案一定更优了。经过若干次这样的操作后，字符串单调不递减并且字典序更小，这与“原来的字符串是最终答案”不符合。于是假设不成立，原命题成立。

这是一个非常好的性质，会帮助我们做题。

首先我们需要先保证 $0$ 的数量最多，再保证 $1$ 的数量最多……所以，我们从小到大考虑每个字符的数量，设当前考虑到的字符为 $j$。

因为答案是单调不递减的，所以每次我们都把所有 $j$，移到除了比 $j$ 小的字符之外，剩下的字符的最前面。因为在当前要保证 $j$ 剩下的尽量多，所以当前这次操作我们所有 $j$ 都不能够删除，只能对比 $j$ 大的字符进行操作。因为每次操作都会使某个字符增大，所以我们要尽量少的操作。

于是，我们得出了一个重要结论：每次要把最后一个 $j$ 之前的比 $j$ 大的字符都移动到最后一个 $j$ 的后面某个位置。

那么这些需要操作的字符应该放到哪个位置呢？

首先，我们先把所有要进行操作的字符，从原来的字符串中移出来单独存放。然后，我们找到比 $j$ 大的最小的字符（如果有的话，这里暂时假设为 $k$），对于 $k$ 来说，我们只要保证 $k$ 字符尽量不影响比它大的字符，所以把 $k$ 都插入在最后一个 $j$ 的后面。然后再把比 $k$ 大的最小的字符插入在最后一个 $k$ 的后面……

于是我们需要动态记录每个字符的最后一个字符的位置，并且维护一个大于等于 $j$ 的当前的字符串。发现插入操作让维护变得棘手。

我们观察上面的过程，发现对于每次插入的字符，大的总会在小的后面，所以可以看成每个字符插入的位置是和它前一个字符的位置是相同的，然后相同的位置当中，小的字符牌在前面。

具体实现的时候我懒，使用了 ```priority_queue```，时间复杂度 $\operatorname O(nm\log n)$，$m$ 为字符数量。您们可以使用桶等东西优化时间复杂度至 $\operatorname O(nm)$。

### 代码

[Codeforces 链接](https://codeforces.com/contest/1730/submission/173821882)。


---

