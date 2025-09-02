# [USACO23JAN] Moo Operations B

## 题目描述

农夫约翰给了奶牛贝西 $Q$ 个新字符串 $(1\le Q\le100)$ ，其中只有字符 `M` 和 `O` ，她想将 $Q$ 个字符串都变成 `MOO`。

贝西可以用如下的方式改变字符串：
- 用相反的字符替换第一个或最后一个字符（将 `M` 变成 `O` ，将 `O` 变成 `M` ）。
- 删除第一个或最后一个字符。

贝西只想用最少的次数完成改变。请你帮她找到需要的最小改变次数。如果不可能在有限的步数中完成这个任务，请输出 `-1` 。

## 说明/提示

### 样例解释 1
将第一个字符串转换为 `MOO`的 $4$ 个操作序列如下：
- 用O替换最后一个字符（操作1）
- 删除第一个字符（操作2）
- 删除第一个字符（操作2）
- 删除第一个字符（操作2）

可以证明，第二个字符串无法转换为 `MOO`。 

第三个字符串已经是 `MOO`，因此无需执行任何操作。

对于 $100\%$ 的测试点，保证 $1 \le Q \le 100$, $ 1\le |S| \le 100$ 。

## 样例 #1

### 输入

```
3
MOMMOM
MMO
MOO```

### 输出

```
4
-1
0```

# 题解

## 作者：LegendaryGrandmaster (赞：12)

[铜组全部题解](https://www.luogu.com.cn/blog/686297/usaco-2023-cu-ti-xie)

首先字符串至少要有 3 位，没有直接输出 -1。

我们三位三位模拟取最小值，只要中间是  `O`，都可以变成  `MOO`。

操作次数如下：

1. `MOO`：0 次。
2. `MOM`：1 次。
3. `OOO`：1 次。
4. `OOM`：2 次。

最终取最小值加上总长度 -3 即可。因为最终只能保留 3 位。如果 $mi$ 仍是初始值，那么输出 -1。

```cpp
#include<bits/stdc++.h>
using namespace std;

signed main()
{
	int t;
	cin>>t;
	while(t--){
		int mi=0x3f3f3f3f;
		string st;
		cin>>st;
		if(st.size()<3){
			puts("-1");
			continue;
		}
		for(int i=0;i<st.size()-2;i++){
			string str=st.substr(i,3);
			if(str=="MOO")mi=min(mi,0);
			else if(str=="MOM")mi=min(mi,1);
			else if(str=="OOO")mi=min(mi,1);
			else if(str=="OOM")mi=min(mi,2);
		}
		if(mi==0x3f3f3f3f)puts("-1");
		else cout<<mi+st.size()-3<<'\n';
	}
}
```

---

## 作者：快斗游鹿 (赞：2)

首先，因为最后要求将字符串变成 $\texttt{MOO}$，所以至少要花费 $len-3$ 的代价执行第一个操作，其中 $len$ 是字符串长度。接下来分类讨论：

如果字符串中本身就包含 $\texttt{MOO}$，那么不需要额外花费代价执行第二个操作。

如果字符串中包含 $\texttt{MOM}$ 或 $\texttt{OOO}$，那么只需要花费 $1$ 的代价执行第二个操作。

如果字符串中包含 $\texttt{OOM}$，那么需要花费 $2$ 的代价执行第二个操作。

否则无解。

```
#include<bits/stdc++.h>
using namespace std;
int Q;
int read(){
	int x=0,f=1;
	char ch=getchar();
	while(ch<'0'||ch>'9'){if(ch=='-')f=-1;ch=getchar();}
	while(ch>='0'&&ch<='9'){x=x*10+ch-'0';ch=getchar();}
	return x*f;
}
int main(){
	Q=read();
	while(Q--){
		string s;cin>>s;
		int flag=0,flag1=0,flag2=0,flag3=0,len=s.length();
		for(int i=0;i<len-2;i++){//MOO
			if(s[i]=='M'&&s[i+1]=='O'&&s[i+2]=='O')flag=1;
		}
		for(int i=0;i<len-2;i++){//MOM
			if(s[i]=='M'&&s[i+1]=='O')flag1=1;
		}
		for(int i=2;i<len;i++){//OOO
			if(s[i-1]=='O'&&s[i]=='O')flag2=1;
		}
		for(int i=1;i<len-1;i++){//OOM
			if(s[i]=='O')flag3=1;
		}
		//cout<<flag<<" "<<flag1<<" "<<flag2<<" "<<flag3<<endl;
		if(flag)printf("%d\n",len-3);
		else if(flag1||flag2)printf("%d\n",len-2);
		else if(flag3)printf("%d\n",len-1);
		else puts("-1");	
	}
	return 0;
}

```

---

## 作者：Loser_Syx (赞：2)

## 闲话

说实话这题特别水，但是作为一个铜组考生，看不懂英文，结果没交代码，赛后一看中文翻译，全会……

## 思路

对于每一个输入的字符串，要把它删除或修改成 `MOO` 样式的字符，首先肯定要进行删除，把它的长度修改成 $3$，那么此时已经进行了 `s.size()-3` 次操作，接下来就是枚举剩下的 $3$ 个字符，首先如果这个字符串是 `MOO` 的话，此时正是最小次数，其次中间的字符是 `M` 的话，这个字符串就是不能将它改变成 `MOO` 的了，对于剩下的两个字符，如果开头的那个字母不是 `M`，操作次数要 $+1$，如果末尾的字母不是 `O`，操作次数也要 $+1$，最后对之前的答案进行取 $\min$ 的操作就可以了，如果答案还是同初始化的一样的话，那么这就是一个无解的字符串，直接输出 $-1$。

## 代码

```cpp
#include<bits/stdc++.h>
using namespace std;
int main(){
	int T;
	scanf("%d", &T);
	while(T--){
		string s;
		cin >> s;
		int ans = 1919810, len = s.size();//ans初始化为一个大点的数字，之后要比较
		for(int i = 0; i <= len - 3; i++){
			string str = s.substr(i, 3);//取一段长度为3的字符串
            int cnt = 0;
			if(str == "MOO"){//已经不用修改了
				ans = 0;
				break;
			}
			if(str[1] == 'M') continue;//中间字符是M，不可能成立
			if(str[0] == 'O') cnt++;//如果开头的是O/不是M，操作次数+1
			if(str[2] == 'M') cnt++;//如果开头的是M/不是O，操作次数+1
			ans = min(ans, cnt);//取min操作
		}
		if(ans == 1919810) puts("-1");//如果没有进行任何一次取min（没有修改原来的值），就是无解
		else printf("%d\n", ans + len - 3);//否则输出
	}
	return 0;
}
```

---

## 作者：DreamLand_zcb (赞：1)

## 简要题意

有 $Q$ 个询问，对于每个询问，给你一个只含有字符“M”和字符“O”的字符串 $S$，求最少要几次**操作 $^{[1]}$**，使字符串 $S$ 变成字符串“MOO”。

**操作** $^{[1]}$：四种操作

* 1.将字符串第一个字符取反（即：“M”变成“O”，“O”变成“M”）

* 2.将字符串最后一个字符取反（即：“M”变成“O”，“O”变成“M”）

* 3.删除字符串第一个字符

* 4.删除字符串最后一个字符

## 思路

首先要确认所有**不可能**经过操作后变成“MOO”的字符串，最容易看出来的是字符串长度 `l < 3`，另一个不可能变成“MOO”的就是在字符串第二个字符到字符串倒数第二个之间没有任何字符“O”的字符串，因为在四种操作中没有任何对中间字符的修改，而且因为每次删除的都是左右两侧的字符，所以最终得到的字符串一定是原字符串中连续的长度为三的一个子串，如果子串中间不是“O”，就不能变成“MOO”。

然后再来确认最小的操作次数，因为最终得到的字符串一定是原字符串中连续的长度为三的一个子串，所以我们只需要枚举第一个字符就行了，如果枚举到的字符的下一个字符不是“O”就跳过，如果是“O”就计算需要改正的次数，将 `ans` 更新。

**最后 $ans$ 不要忘了加上 $l-3$，因为无论怎么删，都要至少把字符串的长度变成 $3$ 此时一共操作了 $l-3$ 次！**
## 代码

```cpp
#include <bits/stdc++.h>
#define ll long long
#define setp setprecision
#define mem(a, m) memset(a, m, sizeof(a));
using namespace std;

int Q;
bool check(string s, int l, int r)//在l~r内有没有"O"
{
	for(int i=l;i<=r;i++)
		if(s[i] == 'O')
			return true;
	return false;
}
int main()
{
	ios::sync_with_stdio(false);
	cin >> Q;
	while(Q--)
	{
		string s;
		cin >> s;
		int l=s.size();
		if(l < 3 || !check(s, 1, l-2))//不可能形成"MOO"字符串
		{
			cout << -1 << endl;
			continue;
		}
		else
		{
			int ans=10, sum=0;
			for(int i=0;i<=l-3;i++)
			{
				if(s[i+1] == 'M')	continue;
				sum=(s[i] == 'O')+(s[i+2] == 'M');
				ans=min(ans, sum);
			}
			ans+=l-3;//加上l-3
			cout << ans << endl;
			continue;
		}
	}
	return 0;
}

```

---

## 作者：doumingze (赞：1)

[题目传送门](https://www.luogu.com.cn/problem/P9012)

# 题意
给定一个由 M 和 O 组成的字符串，输出变为 "MOO" 的最少步数，或报告无解。
变换规则：
* 删除字符串中第一个或最后一个字符。
* 变换字符串中第一个或最后一个字符，即：将 M 变为 O，O 变为 M。

# 分析
我们令 $t$ = "MOO"。

首先处理字符串 $s$ 是否有解的情况。

* $s$ 长度小于 $3$，立刻输出 $-1$。
* 根据变换规则，我们发现：只需要满足 $s$ 中有可以只用变换规则 $2$ 变成 $t$ 的子串，这个询问就是有解的，因为其他的字符可以被我们从头或者尾删去。如果找不到，就是无解的，直接输出 $-1$。

接下来判断最少步。

首先，删去 $s$ 头尾的无用字符，所需步数 $u$ 为 ```s.size()-t.size()```。

然后对剩下来的字符串进行判断。

一共只有 $4$ 个长度为 $3$ 的可以变成 $t$ 的字符串：MOO，OOO，MOM，OOM。他们变成 $t$ 的最少步分别是 $0$，$1$，$1$，$2$。

删完 $s$ 的头尾若干字符后，最后留下的字符串应该为上述 $4$ 个字符串才能确保有解。

设 $step$ 为删去 $s$ 头尾若干字符后剩余字符串变为 $t$ 的最少步数，考虑枚举 $s$ 内长度为 $3$ 的子串，若该字串为上述 $4$ 个字串中的其中一个，就更新 $step$ 取 $min$ 值。

最后输出 $step + u$ 即可，时间复杂度为 $O(nl)$，其中 $l$ 为字符串长度。

# 代码
```cpp
#include<bits/stdc++.h>
using namespace std;

map<string, int> m;

int judge(string s)
{
	if(s.size() < 3) return -1;
	int res = 10000;
	bool fl = false;
	for(int i = 0; i <= s.size() - 3; i ++)
	{
		string t = s.substr(i, 3);
		if(m.count(t)) {
			fl = true;
			res = min(res, m[t]);
		}
	}
	if(!fl) return -1;
	return res;
}

int main()
{
	m["MOO"] = 0;
	m["MOM"] = m["OOO"] = 1;
	m["OOM"] = 2;
	int n;
	cin >> n;
	for(int i = 1; i <= n; i ++)
	{
		string s;
		cin >> s;
		int flag = judge(s);
		if(flag == -1){
			puts("-1");
			continue;
		}
		cout << s.size() - 3 + flag << endl;
	}
	return 0;
}
```

有什么错误或疑问请评论，谢谢！


---

## 作者：鱼跃于渊 (赞：1)

# solution:  
题目要求为给定一个只含 `M` 和 `O` 的字符串，问把它转化为 `MOO` 的最小操作数，如果无法完成输出 `-1` 。有两个操作：
- 将字符串开头或结尾的字符修改为另一个；  
- 删除字符串开头或结尾的字符。  

首先，如果字符串的长度小于 3 时肯定不行；其次，我们可以将任何长度大于 2 的字符串删到只剩 3 个，而首尾的字符串可以修改，那么是否可行就取决于中间的字符是不是 `O` 。到这可以发现，操作次数为字符串长度减一再减字符 `O` 左边是否为 `M` 和右边是否为 `O` 。   
所以解法就出来了，先排除长度小于 3 的字符串，再枚举 1 到字符串长度减二的字符 `O` ，有则更新答案最小值，最后判断答案是否有更新。
# code:  
思路前面已有详细讲解，此处不再多说。
```
#include <bits/stdc++.h>
using namespace std;
string s;
int n;
int solve(){
	if(s.size()<3) return -1;
	int w=1e9;
	for(int i=1,l=s.size()-1;i<l;i++){
		if(s[i]=='O') w=min(w,int(s.size()-1-(s[i+1]=='O')-(s[i-1]=='M')));
	}
	return (w==1e9?-1:w);
}
int main(){
	ios::sync_with_stdio(false);
	cin.tie(0);cout.tie(0);
	cin>>n;
	while(n--){
		cin>>s;
		cout<<solve()<<'\n';
	}
	return 0;
}
```

---

## 作者：Xy_top (赞：0)

USACO Cu 代码最短的一题了，思维难度还是有一点的。

首先这道题可以删除两边的字符串，那么最后剩下的字符串在原串中的位置一定是连续的。

问题就转换成了字符串中连续的三个字符连起来的字符串有没有可能变成 ``MOO``。

因为只能改变两边，中间不能改变，所以能变成 ``MOO`` 的字符串中间肯定是 ``O``。

分情况讨论下就行了，代码很短：

```cpp
#include <iostream>
#include <cstring>
using namespace std;
int T, ans;
string s, t;
int main(){
	cin >> T;
	while (T --) {
		ans = 100000;
		cin >> s;
		if (s.size () < 3) {
			cout << -1 << "\n";
			continue;
		}
		for (int i = 0; i < s.size () - 2; i ++) {
			t = s.substr (i, 3);
			if (t == "MOO") ans = s.size () - 3;
			else if (t == "MOM" || t == "OOO") ans = min (ans, int (s.size () - 2) );
			else if (t == "OOM") ans = min (ans, int (s.size () - 1) );
		}
		if (ans == 100000) cout << -1 << "\n";
		else cout << ans << "\n";
	}
	return 0;
}
```


---

## 作者：Jorisy (赞：0)

首先观察题目。

操作是在**两端**进行删除或修改。

因此，要变成 $\texttt{MOO}$，中间的 $\texttt O$ 是无法修改的。

也就是说，字符串 $\texttt{MOO,MOM,OOO,OOM}$ 都是可以变成 $\texttt{MOO}$ 的。

所以如果字符串没有 $\texttt O$ 必定无解。

然后我们遍历字符串处理子串即可。

赛时 AC Code：
```cpp
#include<bits/stdc++.h>
using namespace std;

void sol()
{
	string s;
	cin>>s;
	int ans=1e9;
	for(int i=1;i<s.size()-1;i++)
	{
		string t=s.substr(i-1,3);
		if(t=="MOO")//不用改字符
		{
			cout<<s.size()-3<<endl;
			return;
		}
		if(t=="MOM"||t=="OOO") ans=min(ans,(int)s.size()-2);//只要改变前面或后面的字符
		if(t=="OOM") ans=min(ans,(int)s.size()-1);//前后的字符都要改
	}
	if(ans==(int)1e9) puts("-1");//无解
	else cout<<ans<<endl;
}

int main()
{
	int t;
	cin>>t;
	while(t--) sol();
	return 0;
}
```

---

## 作者：so_find_skind (赞：0)

~~我又来了。~~

## 题目思路

没什么好说的，就一个普通的字符串问题。

其实看条件就会发现，问题在于**最后的字符串**，因为首先对于字符串，因为最后的 `MOO` 长度为 3，因此最后的操作肯定是长度为 3 的字符串进行了 $x$ 次更改操作，因此当它成立时，次数必然大于等于 $t-3$（这里先把 $t$ 赋值为字符串长度），因此我们枚举最后得到的字符串，取最终值的最小值即可。

现在看字符串最后情况下的各种情况（~~绕口令？！~~）即可。

无解：`OMO`、`OMM`、`MMO`、`MMM` 共四种。

一次操作：`MOM`、`OOO` 共两种。

两次操作：`OOM` 一种。

因此代码也不难写了。

AC Code：

```
#include<bits/stdc++.h>
using namespace std;
int n,ans;
string s;
void cj(){//字符串s最后的最佳情况
	for(int i=0;i<s.size()-2;i++){
		if(s[i]=='M' && s[i+1]=='O'){
			s=s.substr(i,3);
			return;
		}
	}
	for(int i=1;i<s.size()-1;i++){
		if(s[i]=='O' && s[i+1]=='O'){
			s=s.substr(i-1,3);
			return;
		}
	}
	int q=s.find("OOM");
	if(q==-1)
		q=0;
	s=s.substr(q,3);
}
int main(){
	cin>>n;
	while(n--){
		cin>>s;
		if(s.size()<3){//必无解，注意如果不特判会WA
			cout<<"-1\n";
			continue;
		}
		if(s.find("MOO")!=-1){//都存在MOO了就不用再枚举情况了
			cout<<s.size()-3;
		}else{
			ans=s.size()-3;
			cj();
			if(s=="MMO" || s=="OMO" || s=="MMM" || s=="OMM")
				cout<<-1;
			else if(s=="MOM" || s=="OOO")
				cout<<ans+1;
			else
				cout<<ans+2;
		}
		cout<<"\n";
	}
	return 0;
}

```

---

