# Arthur and Brackets

## 题目描述

你需要构造一个长为 $2n$ 的小括号序列 $S$，左、右括号各 $n$ 个。

对于从左到右的第 $i$ 个左括号 $S_a$，需要与其配对的右括号 $S_b$ 满足 $b - a \in [L_i, R_i]$。

## 样例 #1

### 输入

```
4
1 1
1 1
1 1
1 1
```

### 输出

```
()()()()
```

## 样例 #2

### 输入

```
3
5 5
3 3
1 1
```

### 输出

```
((()))
```

## 样例 #3

### 输入

```
3
5 5
3 3
2 2
```

### 输出

```
IMPOSSIBLE
```

## 样例 #4

### 输入

```
3
2 3
1 4
1 4
```

### 输出

```
(())()
```

# 题解

## 作者：_Album_ (赞：8)

更好的阅读:[传送门](https://payphone-x.github.io/2019/11/09/CF508E/)

-----------------

## 分析

一道比较简单的贪心。

题面很明确地告诉我们，这是一道括号匹配问题。因此我们考虑使用栈模拟。

在模拟时不难发现，只有当栈顶的括号被匹配之后，后面的括号才有可能被匹配。

So，我们只需要优先匹配栈顶括号即可。

剩下的就是模拟了，直接看代码注释吧……

----------------------------------

## Code[Accepted]

```Cpp
#include <bits/stdc++.h>

#define ll long long 
#define I inline
#define N 1501

using namespace std;


ll n , l[N] , r[N] , p[N];  //p[i]表示左括号i之前有多少括号
char ans[N];
bool flag = true;
stack<int > S;

int main(){
    cin >> n;
    ll cnt = 0; //cnt为当前的括号总数
    for(int i = 1; i <= n; i ++){
        cin >> l[i] >> r[i];
        S.push(i);
        p[i] = cnt;
        ans[++ cnt] = '(';
        while(!S.empty()){
            int top = S.top();
            if(r[top] + p[top] < cnt){  
            //如果当前括号的右端点 + 该括号之前的括号数量小于当前括号总数，则不可能满足
                flag = false;   
                break;
            }
            if(l[top] + p[top] > cnt){
            //如果当前括号左端点 + 该括号之前的括号数量大于当前括号总数，则等待之后的左括号补位。
                break;
            }
            ans[++ cnt] = ')';  //否则就进行匹配
            S.pop();    
        }
    }
    if(S.empty() && flag == true){  //若最后没有未匹配的括号且都可以满足，则当前序列满足条件
        for(int i = 1; i <= n * 2; i ++){
            cout << ans[i];
        }
    }    
    else{
        puts("IMPOSSIBLE");
    }
    return 0;
}
```

------------------------------------

# THE END



---

## 作者：狂风之息 (赞：5)

这题主要运用了**贪心**算法。

贪心策略：对于第 $i$ 对括号，当左括号与右括号的距离大于等于 $l_i$ 时，就不再向当中加入括号。

即：对于一个括号序列 $(a)$，左右两侧的括号为第 $i$ 对括号，当 $|a|\geq  l_i-1$ 时，我们认为第 $i$ 对括号匹配完成。

因为当 $(a)$ 匹配成功时，$(a)b$  一定可以匹配成功( $a,b$ 都为合法的括号序列),而序列 $(ab)$ 有可能不满足左右括号的距离(即 $|a|+|b|\geq r_i$ )，而且序列 $(a)b$ 和序列 $(ab)$ 长度相等，因此对于更外部的括号匹配效果完全一致。

关于**判断不可能**

$1.$ 因为我们括号内的序列是尽量选取最短的，所以，如果第 $i$ 对括号匹配完毕后发现 $|a|\geq r_i-1$ (括号内序列太长了)就说明第 $i$ 对括号不可能匹配。

$2.$ 此外，当前括号尚未匹配完成时，却发现已经没有剩余的括号了，也是不可能匹配成功的。

算法时间复杂度 $O(n)$.

~~码风不好请见谅~~

code： 
```cpp
#include<bits/stdc++.h>
using namespace std;

long long l[1000],r[1000];
int pos;
int n;
int len;

char s[2000];

bool flag=0;

int dfs(int p) //递归求解
{
    s[++len]='(';
    int v=0;
    while (v<l[p]-1&&++pos<=n) //只要达到匹配要求就停止添加
        v+=dfs(pos);
    if (v>r[p]-1||v<l[p]-1) flag=1; //序列太长或者太短都不行
    s[++len]=')';
    return v+2; //返回括号序列的长度
}

int main()
{
    scanf("%d",&n);
    for (int i=1;i<=n;i++)
        scanf("%d %d",l+i,r+i);
    while (++pos<=n)
        dfs(pos);
    if (!flag) printf("%s",s+1);
    else puts("IMPOSSIBLE");
}
```


---

## 作者：ykzzldz (赞：4)

总的来说，这道题目还是比较有意思的，是一道贪心。

思路就是先将每个新的左括号加入栈，此时可以加入一个右括号匹配左括号并将左括号弹出，或者不进行操作。

贪心的部分就是在：如果有一个右括号和左括号相匹配，那么就直接弹出左括号，让其与右括号匹配。

关于贪心的证明：因为入栈的括号均为左括号，所以如果当前的右括号不能与栈顶的左括号相匹配，那么也不能与后面的其他括号相匹配，得到本题的贪心是正确的。

下面贴上代码：

```
#include <iostream>
#include <cstdio>
#include <cmath>
#include <algorithm>
#include <cstring>
#include <string>
#include <queue>
#include <stack>
#include <map>
using namespace std;
bool flag=true;
int n,l[610],r[610],jsq,q[610],cnt;
char ans[2000];
int main()
{
    cin>>n;
    for(int i=1;i<=n;i++)
    {
    	jsq++;
    	cin>>l[jsq]>>r[jsq];
    	q[jsq]=cnt;
    	ans[++cnt]='(';
    	while(jsq)
    	{
    		if(r[jsq]<cnt-q[jsq])
    		    flag=false;
    		if(l[jsq]>cnt-q[jsq])
    		    break;
    		jsq--;
    		cnt++;
		}
    }
    if(flag&&!jsq)
    {
    	for(int i=1;i<=n*2;i++)
    	{
    		if(!ans[i])ans[i]=')';
    		cout<<ans[i];
		}
	}
	else cout<<"IMPOSSIBLE";
	cout<<endl;
    return 0;
}
```

---

## 作者：_Yoimiya_ (赞：3)

[题目传送门。](https://www.luogu.com.cn/problem/CF508E)

解题思路：
- 首先考虑“IMPOSSIBLE”的情况。当一个左括号要求右括号的区间在自身位置之前时，无法满足。同时当最终的答案中左右括号不等时，无法满足。  

- 其次考虑配对顺序。我们知道，每个左括号对应一个区间。因为前面的左括号在后面的左括号未解决前无法配对，所以我们要尽量将每一个括号早配对，这样有益于前面的配对操作。这其实是一个简单的贪心思想。

- 那如何填左括号呢？很简单，我们把没法填右括号的位置填上左括号就行了。这里我用了一个单调栈来维护，在填的同时检查是否无法实现。  

- 填完后，判断是否合法，输出即可。

AC代码
```cpp
#include<bits/stdc++.h>
using namespace std;
const int M(1201);
int n,pre[M],q[M],tot,opt;
struct node{
	int id,l,r;
};node t[M];
node st[M];
string ans;
signed main(){
	ios::sync_with_stdio(false);
	cin.tie(0);cout.tie(0);
	cin>>n;int top(0);
	for(register int i(1);i<=n;++i) cin>>t[i].l>>t[i].r,t[i].id=i;
	for(register int i(1);i<=n;++i){
		st[++top]=t[i];pre[i]=tot;ans+="(";++tot;++opt;
		while(top){
			node news(st[top]);
            if(news.r+pre[news.id]<tot) {
            	cout<<"IMPOSSIBLE";return 0;
			}
			else if(news.l+pre[news.id]>tot) break;
			ans+=")";++tot;--opt;--top;
		}
	}
	cout<<(opt==0?ans:"IMPOSSIBLE");return 0;
}
```

---

## 作者：leozhang (赞：1)

贪心题是很有趣的...

首先，本题为括号匹配问题，那么可以考虑进行栈模拟

然后，我们思考一下如何匹配：虽然题目中仅对右括号的位置提出了区域性要求，但可以发现，对能匹配上的栈顶括号立刻进行匹配一定是一种最优解！

为什么？

根据括号匹配原则，如果栈顶括号未被匹配，那么其他括号将无法被匹配，那么栈顶括号越长时间不被匹配，栈内括号失配的可能就越大。相反，如果我们对能匹配的栈顶括号立刻进行匹配，不会存在反例使得本能匹配上的其他括号未能被匹配。

所以这题的剩余部分就变成了一个模拟...

```cpp
#include <cstdio>
#include <cmath>
#include <cstring>
#include <cstdlib>
#include <iostream>
#include <algorithm>
#include <queue>
#include <stack>
using namespace std;
int l[605],r[605];
int n;
int my_stack[605];
int posi[605];
int ttop=0;
int typ[1205];
int main()
{
	scanf("%d",&n);
	for(int i=1;i<=n;i++)
	{
		scanf("%d%d",&l[i],&r[i]);
	}
	int pos=2;
	int cnt=1;
	typ[1]=1;
	my_stack[++ttop]=1;
	posi[ttop]=1;
	while(pos<=2*n)
	{
		int t=my_stack[ttop];
		int p=posi[ttop];
		if(p+l[t]<=pos&&p+r[t]>=pos)
		{
			typ[pos]=2;
			ttop--;
			pos++;
		}else
		{
			my_stack[++ttop]=++cnt;
			posi[ttop]=pos;
			typ[pos]=1;
			pos++;
		}
	}
	if(ttop)
	{
		printf("IMPOSSIBLE\n");
		return 0;
	}else
	{
		for(int i=1;i<=2*n;i++)
		{
			if(typ[i]==1)
			{
				printf("(");
			}else
			{
				printf(")");
			}
		}
		printf("\n");
	}
	return 0;
}
```

---

## 作者：Rosent (赞：0)

简单贪心括号匹配问题。

我们可以使用一个栈维护括号的匹配顺序。

贪心策略：如果可以匹配，则每次优先匹配栈顶的左括号。之后再匹配下一个左括号。该题转化为一个基本黄色贪心。

不难证明上述的贪心策略的正确性，由于左括号总是与距离其最近的一个右括号匹配，所以如果不先匹配栈顶的左括号，后续的括号都无法匹配，所以要先匹配栈顶括号。

不可行的特判：
1. 如果该左括号之前的括号数量 $+$ 与其配对的右括号的最远距离 $>$ 当前匹配的括号序列长度 则该括号一定无法配对。
2. 如果在整个序列都匹配结束后，栈不为空，则没有满足条件的匹配方法。


代码如下
```cpp
#include <bits/stdc++.h>
using namespace std;
const int maxn=610*2;//括号序列长度记得*2
struct n
{
	int l,r;
}a[maxn];
stack<int> s;
char q[maxn];
int num[maxn];
int main()
{
	int n;
	cin>>n;
	for(int i=1;i<=n;i++)
	{
		cin>>a[i].l>>a[i].r;
	}
	int p=0;
	for(int i=1;i<=n;i++)
	{
		s.push(i);
		num[i]=p;
		q[++p]='(';
		while(!s.empty())
		{
			if(a[s.top()].r+num[s.top()]<p)
			{
				cout<<"IMPOSSIBLE";
				return 0;
			}
			if(a[s.top()].l+num[s.top()]>p)
			{
				break;
			}
			q[++p]=')';
			s.pop();
		}
	}
	if(!s.empty())
	{
		cout<<"IMPOSSIBLE";
		return 0;
	}
	for(int i=1;i<=n*2;i++)
	{
		cout<<q[i];
	}
	return 0;
}
```

---

## 作者：lizhous (赞：0)

[洛谷传送门](https://www.luogu.com.cn/problem/CF508E)

[CF传送门](https://codeforces.com/contest/508/problem/E)

## 分析
**一个显然的结论**：因为括号不能跨括号匹配，所以对于一个左括号，它可以被右括号匹配，当且仅当它与右括号之间的所有括号都已被匹配，否则必然存在一个未被匹配的括号与两个括号中的一个匹配。  

根据此结论，我们想出一种贪心：对于一个左括号，若可以匹配，我们就立刻为它匹配右括号。

**正确性证明**：  
对于已匹配的括号：显然影响不到。  
对于正在匹配的括号：在加入新左括号后，必然要等到它匹配完才可以进行匹配，可能将可以匹配的括号变为无法匹配（超过长度），不会将无法匹配的括号变为可以匹配，所以不会更优。  
对于未匹配的括号：未开始匹配，后面的长度未开始统计；添加顺序也不会改变；无影响。

对于每一位，若前一个左括号无法匹配（短于长度），就插入新左括号。若左括号超过长度，因为已经是最优情况，所以可以直接输出无解。代码部分使用栈维护即可。时间复杂度 $O(2n)$。

## 代码
```cpp
#include<iostream>
#define int long long
using namespace std;
int n, l[1000001], r[1000001], w;
struct stack {
	int r, l, w;
} st[1000001];
int len, num;
char ans[1000001];
signed main() {
	scanf("%lld", &n);
	for (int i = 1; i <= n; i++) {
		scanf("%lld%lld", &l[i], &r[i]); //输入
	}
	for (int i = 1; i <= n; i++) {
		st[++len].r = r[i]; //加入新左括号
		st[len].l = l[i];
		st[len].w = num;
		ans[++num] = '('; //ans数组记录结果
		while (len) { //匹配右括号
			if (st[len].r < num - st[len].w) { //如果超过长度
				cout << "IMPOSSIBLE"; //无解
				return 0;
			}
			if (st[len].l > num - st[len].w) { //如果这个左括号还没到匹配长度
				break; //结束匹配右括号
			}
			len--; //出栈
			ans[++num] = ')'; //ans数组记录
		}
	}
	if (len) { //如果左括号没有匹配完
		cout << "IMPOSSIBLE"; //无解
		return 0;
	}
	for (int i = 1; i <= num; i++) {
		cout << ans[i]; //输出ans
	}
}
```


---

## 作者：XL4453 (赞：0)

### 解题思路：

考虑贪心。

维护一个栈存放左括号，每一个左括号依次加入栈中，弹栈即为匹配括号。

那么就有两种操作，将这个新的左括号加入栈中表示使其处于待匹配的状态，或者加入一个右括号使顶部左括号弹出。

这个问题的贪心策略是：对于一个栈顶左括号，如果在一个时刻能通过加右括号的形式使其匹配，那么一定直接弹出。

---

然后考虑其正确性：

假设当前的左括号正处于可以匹配的状态，如果此时再往这个栈中添加左括号，就有可能使得当前括号不匹配了，而立即弹出也可以尽可能的使得之前还在栈中的左括号更有可能获得匹配。

另一方面，由于每一次的加入右括号只能和栈顶左括号匹配，如果当前的括号还不能匹配，那么如果强行加入括号也并不能和前面的某一个括号匹配。

---
### 代码：

```cpp
#include<cstdio>
using namespace std;
int st[606][2],le[606],n,l,r,top,cnt;
int k[1206];
int main(){
	scanf("%d",&n);
	for(int i=1;i<=n;i++){
		scanf("%d%d",&l,&r);
		st[++top][0]=l;
		st[top][1]=r;
		le[top]=cnt;
		k[++cnt]=1;//(
		while(top){
			if(st[top][1]<cnt-le[top])
			return 0&printf("IMPOSSIBLE\n");
			if(st[top][0]>cnt-le[top])break;
			cnt++;top--;
		}
	}
	if(top)return 0&printf("IMPOSSIBLE\n");
	for(int i=1;i<=2*n;i++)
	printf("%c",k[i]==1?'(':')');
	printf("\n");
	return 0;
}
```


---

## 作者：聊机 (赞：0)

关于贪心做法已经非常清晰了，这里介绍一种 DP 做法，请求打开题解通道。

关于本题 DP 做法我能想到的唯一优势，就是可以计算方案数，或求特定合法序列。

**状态设计**：$f[i][j]$ 表示第 $i$ 个括号，在答案序列中向后延伸 $j$ 的长度能否合法，注意与它本身配对的括号不一定在往后 $j$ 的位置，如果合法，那么第 $i$ 个左括号配对的右括号在后方多远的位置。这里注意 $j$ 都为奇数，因为括号都是一对一对的。

如果要计数，可以再加一个计数的变量。

**状态转移**（注意此处的 $j$ 与上文不同）：

在 $l_i$，$r_i$ 的范围内，先寻找一个奇数 $j$ 使得 $f[i-1][j-2]$ 不为 $0$，这意味着我们可以在这个地方给第 $i$ 个左括号配右括号，然后向后枚举奇数 $k$，因为在 $j$ 的范围内有本身的一个右括号，所以还有 $j/2$ 对括号（向下取整），如果 $f[i+j/2+1][k]$ 不为 $0$，即用 $j$ 来更新 $f[i][j+k+1]$，可以计数。

因为此题本身只要求任意合法序列，所以可以直接覆盖 DP 值，但是这个做法我们还可以求最小或最大字典序的合法序列，以及计算合法序列数量。

最后如果 $f[1][n\times 2-1]$ 不为 $0$，就递归输出序列，否则无解，输出见代码。

复杂度比贪心差。

```cpp
#include<bits/stdc++.h>
using namespace std;
typedef long long ll;
inline int qr() {
	int k=0,f=1;char ch=getchar();
	while(!isdigit(ch)){if(ch=='-')f=-1;ch=getchar();}
	while(isdigit(ch))k=(k<<1)+(k<<3)+(ch^48),ch=getchar();
	return k*f;
} 

int n;
int l[602],r[602];
int f[602][1202];
char ans[1202];
void dfs(int x,int i,int j) {
	ans[x]='(';
	ans[x+f[i][j]]=')';
	if(f[i][j]>1) dfs(x+1,i+1,f[i][j]-2);
	if(f[i][j]<j) dfs(x+f[i][j]+1,i+f[i][j]/2+1,j-f[i][j]-1);
}
int main() {
	n=qr();
	for(int i=1;i<=n;i++) {
		l[i]=qr(),r[i]=qr();
		if(l[i]%2==0) ++l[i];
	}
	if(l[n]>1) {puts("IMPOSSIBLE");return 0;}
	f[n][1]=1;
	for(int i=n-1;i>=1;i--) {
		for(int j=l[i];j<=r[i];j+=2) {
			if(j==1||f[i+1][j-2]) {
				f[i][j]=j;
				int x=i+j/2+1;
				if(x>n) continue;
				for(int k=l[x];k<=(n-x+1)*2;k+=2) 
					if(f[x][k]) f[i][j+k+1]=j;
			}
		}
	}
	if(!f[1][n*2-1]) {puts("IMPOSSIBLE");return 0;}
	dfs(1,1,n*2-1);
	for(int i=1;i<=n*2;i++) 
		putchar(ans[i]);
	return 0;
}
```

---

