# [ARC113C] String Invasion

## 题目描述

[problemUrl]: https://atcoder.jp/contests/arc113/tasks/arc113_c

長さ $ N $ の文字列 $ S $ が与えられます。$ S $ の $ i $ 文字目を $ s_i $ で表します。以下の操作を繰り返せる回数の最大値を求めてください。

- 連続する $ 3 $ 文字 $ s_i,s_{i+1},s_{i+2}\quad\ (1\leq\ i\leq\ |S|-2) $ であって、$ s_i=s_{i+1}\neq\ s_{i+2} $ であるものを選ぶ。$ s_{i+2} $ を $ s_i $ で置き換える。

## 说明/提示

### 制約

- $ 3\ \leq\ |S|\ \leq\ 2\times\ 10^5 $
- $ S $ は英小文字からなる

### Sample Explanation 1

以下のように $ 3 $ 回の操作を行うことができます。 - $ i=2 $ に対して操作を行う。操作後の文字列は `acccpt` になる。 - $ i=3 $ に対して操作を行う。操作後の文字列は `acccct` になる。 - $ i=4 $ に対して操作を行う。操作後の文字列は `accccc` になる。

## 样例 #1

### 输入

```
accept```

### 输出

```
3```

## 样例 #2

### 输入

```
atcoder```

### 输出

```
0```

## 样例 #3

### 输入

```
anerroroccurred```

### 输出

```
16```

# 题解

## 作者：Binary_Lee (赞：4)

## [题面传送门](https://www.luogu.com.cn/problem/AT_arc113_c)

### 解决思路

题目大意是给你一个字符串 $s$，定义一次操作为对于长度为 $3$ 的一个子段，满足 $s_i=s_{i+1}\ne s_{i+2}$，则可以将 $s_{i+2}$ 变为 $s_i$。问最多可以操作多少次。

首先可以对照样例三找出规律。对于样例三 `anerroroccurred`，最优的操作方法是：

- 先 $2$ 后变成 `anerroroccurrrr`（改 `r`）

- 再 $5$ 次变成 `anerroroccccccc`（改 `c`）

- 再 $9$ 次变成 `anerrrrrrrrrrrr`（改 `r`）

可以发现，最优策略是从后往前找，每次找到可以操作的，就把它后面的所有字母都变成一样的。

假设字符串长度为 $n$，并且 $s_i=s_{i+1}$，则可以操作的次数是 $n-(i+2)-(sum_{s_i}-2)$，其中，$n-(i+2)$ 算出之后有几个字符。$sum_{s_i}$ 表示：**当前字符串**、**当前操作位置及之后位置** 有多少个字符为 $s_i$。因为重复的字符不能操作，所以要减掉，又因为第 $s_i,s_{i+1}$ 位不算，所以减 $2$。

一次修改后，之后的字符都变相同了，所以将 $sum$ 清空，同时赋 $sum_{s_i}$ 为 $n-i$。

### AC Code

```cpp
#include<bits/stdc++.h>
#define IOS ios::sync_with_stdio(false)
#define TIE cin.tie(0),cout.tie(0)
#define int long long
using namespace std;
string s;
int sum[200],ans;
signed main(){	
	IOS;TIE;
	cin>>s;
	sum[s[s.size()-1]]++;
	sum[s[s.size()-2]]++;
	for(int i=s.size()-3;i>=0;i--){
		sum[s[i]]++;
		if(s[i]==s[i+1]&&s[i+1]!=s[i+2]){
			ans+=s.size()-i-sum[s[i]];
			for(int j='a';j<='z';j++) sum[j]=0;
			sum[s[i]]=s.size()-i;
		}
	}
	cout<<ans<<endl;
	return 0;
}
```

---

## 作者：So_noSlack (赞：2)

[洛谷链接](https://www.luogu.com.cn/problem/AT_arc113_c)&[Atcoder 链接](https://www.luogu.com.cn/remoteJudgeRedirect/atcoder/arc113_c)

本篇题解为此题**较简单做法**及**较少码量**，并且码风优良，请放心阅读。

## 题目简述

现在有一个字符串 $S$，每一次你可以选择一个 $i(1 \le i \le | S |)$，如果 $S_i = S_{i + 1} \ne S_{i + 2}$。就可以将 $S_{i + 2}$ 设为 $S_i$
  
求**最多**能操作几次。

## 思路

本题比较贪心，让我们先来造一个样例解释一下：

如 `abbfioidddssabsaa` **最优**的方案是：

- 先操作 $4$ 次变为 `abbfioidddsssssss`。

- 再操作 $7$ 次变为 `abbfioidddddddddd`。

- 最后操作 $14$ 次变为 `abbbbbbbbbbbbbbbb`。

这样**最大总操作次数**为 $25$ 次。

从这个样例中可以发现**贪心思路**，要想**总操作次数最大化**，就需要**从后到前**去操作，如果**从前到后**操作那么后面可操作的连续字母就会被覆盖，这样**总操作次数就不是最大**了。

对于每次操作，最优的是**把后面的所有不相同的字母变为一样**，这就涉及到一个问题，**如果后面有相同字母如何判断**？其实**不必**再从当前位置往后搜，只需要定义一个 $num$ 一维数组用 $num_i$ **表示当前位置的后面字母 $i$ 的个数**。

对于 $num$ 数组需要**在搜的过程中处理**。如果遇到可以替换的情况就把**当前位置后的字母**全变为**当前字母**，同时需**清空** $num$ 数组的记录，**把当前位置的字母数记录**即可。

替换后，$ans$ 需增加 $n - i$，考虑到**后面的相同字母**，所以就需要用到我们**维护**的 $num$ 数组了，所以操作数需减去 $num_{str_{i}-'a'}$。

经过以上分析及优化后，很容易即可写出**代码**了：

```cpp
#include<iostream>
using namespace std;

string str;
long long ans = 0, num[205];

int main() {
	cin >> str;
	int n = str.length(); // 记录 str 的长度
	num[str[n - 1] - 'a'] ++, num[str[n - 2] - 'a'] ++; // 初始化 num 数组
	for(int i = n - 3; i >= 0; i --) {
		num[str[i] - 'a'] ++; // 记录此位置的字母
   		// 满足替换的条件
		if(str[i + 1] != str[i + 2] && str[i] == str[i + 1]) {
			ans += n - i - num[str[i] - 'a'];
			for(int j = 0; j < 26; j ++) num[j] = 0; // 清空 num 数组
			num[str[i] - 'a'] = n - i; // 记录替换后的字母数
		}
	}
	cout << ans << endl; // 输出，换行好习惯
	return 0;
}
```

[提交记录](https://www.luogu.com.cn/record/117670273)

$$\text{The End!}$$

---

## 作者：zimujum (赞：1)

## [题目在这](https://www.luogu.com.cn/problem/AT_arc113_c)


------------
## 题目描述
在一个只有小写字母的字符串中，如果有两个连续的字母相同，就将它们后面的所有字母变为它们，问最多变换了多少个字母。


------------
## 分析
按照样例三 `anerroroccurred` 中，我们的方案是：

第一步将字符串变为 `anerroroccurrrr`，操作两次；

第二步将字符串变为 `anerroroccccccc`，操作五次；

第二步将字符串变为 `anerrrrrrrrrrrr`，操作九次；

总共十六次。

由此可看出，我们可以从后往前捋，这样子就可以做到最多的变换次数。



------------
## 做法

### First

我们可以进行暴力，从后往前依次暴力，最后找出答案。但是时间复杂度太大，实测会超时；

#### 暴力代码

```
#include <bits/stdc++.h>
#define itn int
#define ll long long
#define ull unsigned long long
#define AC return 0
using namespace std;
const ll M=114514;
string s;
ll sum;
int n;
int nb(char c,int m){
	int ans=0;
	for(int i=m;i<n;i++){
		if(s[i]!=c){
			ans++;
			s[i]=c;
		}
	}
	return 	ans;
}
int main(){
//	freopen(".in","r",stdin);
//	freopen(".out","w",stdout);
	cin >> s;
	n=s.size();
	for(int i=n-1;i>=0;i--){
		if(s[i]==s[i+1]&&s[i+1]!=s[i+2]) sum+=nb(s[i],i+2);
	}
	cout << sum;
//	fclose(stdin);
//	fclose(stdout);
	AC;
}


```

[TLE](https://www.luogu.com.cn/record/137561187) 珍贵画面。

### AC 思路

我们定义一个变量，在从后往前的遍历中储存每个字母的出现次数，在找到符合条件的地方时，将除去该字母以外的所有字母的数量增加到 $sum$ 中，记得清零，不然会重。

#### 代码

```
#include <bits/stdc++.h>//万能头开头
#define itn int
#define ll long long
#define ull unsigned long long
#define AC return 0
using namespace std;
const ll M=114514;
string s;
ll sum,ans;
int n;//储存每个字母的出现次数
int v[27];
int main(){
//	freopen(".in","r",stdin);
//	freopen(".out","w",stdout);
	cin >> s;
	n=s.size();
	for(int i=n-1;i>=0;i--){
		if(s[i]==s[i+1]){//当符合条件时
			sum+=ans-v[s[i]-'a'+1];//将除去该字母以外的所有字母的数量增加
//			if(s[i]!=c[j]){
//				sum+=v[j];
//				v[s[i]-'a'+1]+=v[j];
//				v[j]=0;
//			}
			memset(v,0,sizeof(v));//清零，防止重复
			v[s[i]-'a'+1]=ans;//将其他的所有字母变为该字母
		}
		v[s[i]-'a'+1]++;//将该字母计数
		ans++;//总量
	}
	cout << sum;//输出
//	fclose(stdin);
//	fclose(stdout);
	AC;//功德圆满
}


```

打完哩。

有错误记得指出！

---

## 作者：max666dong123 (赞：1)

## 题意
给定一个字符串 $S$，每次可以选择一个 $i(1 \le i \le |S|)$，如果 $s_i=s_{i+1}\ne s_{i+2}$，就将 $s_{i+2}$ 设为 $s_i$。求最大的操作次数。

## 思路
选择 $i$ 变换其实就是找到两个相同的数，$s_i$ 和 $s_{i+1}$ 然后把后面所有的数全部变为 $s_i$，直到有 $s_j=s_i$ 为止。
举个例子 ``anerroroccurrrr`` 从第 $9$ 个和第 $10$ 个开始变，可以变为 ``anerroroccccccc``。

就会发现可以用贪心做，从后往前找一定是最优的，因为从前往后找会覆盖掉后面的可以变换的字母。

## 实现
记录一个 $cnt_i$ 表示字母 $i$ 出现了多少次，每次统计答案为 $len-i-cnt_{s_i}$，再更新 $cnt_{s_i}=len-i$ 即可。

## 代码
```cpp
#include<bits/stdc++.h>
#define int long long
using namespace std;
string k;
int sum[200009];
signed main(){
	cin>>k;
	sum[k[k.length()-1]]++;
	sum[k[k.length()-2]]++;
	long long cnt=0;
	for(int i=k.length()-3;i>=0;i--){
	sum[k[i]]++;
		if(k[i]==k[i+1]&&k[i]!=k[i+2]){
			//cnt++;
//			cnt+=k.length()-i-1;
//			cout<<k.length()-i-1<<endl;
//			for(int j=i;j<k.length();j++){
//				if(k[j]!=k[j-1]){
//					cnt++;
//				//	cout<<j<<endl;
//					k[j]=k[j-1];
//				}
//
//			}
			
			cnt=cnt+k.length()-i-sum[k[i]];
			for(int j='a';j<='z';j++){
				sum[j]=0;
			}
			sum[k[i]]=k.length()-i;
		} 
	}
	printf("%lld",cnt);
	return 0;
}

```

---

## 作者：_shine_ (赞：1)

## 题目大意
现在有一个字符串 $S$，每一次你可以选择一个 $i\left ( 1\le i \le \left | S \right |  \right ) $，如果 $S_i = S_{i+1} \ne S_{i+2} $，就可以将 $S_{i+2}$ 设为 $S_i$。

现问你最多能操作几次。
## 思路
我们可以先来模拟一下样例 ```anerroroccurred```：

先是在 $12$ 和 $13$ 个字母 ```rr```上，符合条件，修改后面的 ```ed```，则字符串 $S$ 变成了 ```anerroroccurrrr```。

然后在 $9$ 和 $10$ 个字母 ```cc```上，符合条件，修改后面的 ```urrrr``` ，则字符串 $S$ 变成了 ```anerroroccccccc```。

最后在 $4$ 和 $5$ 个字母 ```rr```上，符合条件，修改后面的 ```oroccccccc``` ，则字符串 $S$ 变成了```anerrrrrrrrrrrr```。

我们可以试着模拟更多的方法，最终可以发现，这道题其实较为简单，可以直接从后往循环一遍，每次记录一下不同的字母出现的次数，在每次可以进行操作时，直接进行操作，无需计算（这样一定是最优的），每次把记录数组清空，记录为当前操作的字母出现 $len-i$ 次（$len$ 为字符串 $S$ 长度），并且记录并输出答案就可以了。
## Code
```cpp
#include<bits/stdc++.h>
using namespace std;
#define int long long
const int maxn=2e5+10;
const int maxm=2e2; 
char s[maxn];
int cnt[maxm],ans;
signed main(){
	cin >> s;
	int len=strlen(s);
	for(int i=len-1;i>0;--i){
		cnt[s[i]]++;
		if(s[i]==s[i-1] && s[i-1] != s[i-2]){
			ans+=len-i;
//			cout << ans << " " << cnt[s[i]] << " " << i << " " << s[i] << endl;
			ans-=cnt[s[i]];
			memset(cnt,0,sizeof(cnt));
			cnt[s[i]]=len-i;
		}
	}
	cout << ans << endl;
	return 0;
}
```


---

## 作者：_Weslie_ (赞：0)

## [题目传送门。](https://www.luogu.com.cn/problem/AT_arc113_c)

给定一个字符串 $s$，若 $s_i=s_{i-1}$ 且 $s_{i+1}\neq s_{i+2}$ 则将 $s_{i+2}$ 改为 $s_i$。问最多能操作几次。

还是看一下样例：

```anerroroccurred```，未改变。

```anerroroccurrrr```，改变 $2$ 次。

```anerroroccccccc```，改变 $7$ 次。

```anerrrroccccccc```，改变 $8$ 次。

```anerrrrrrrrrrrr```，改变 $16$ 次。

可以看出，若找到一个可以变换的，就直接让答案加上后面的字符数量。

然后，输出 $17$。

原因是，我们没有计算重复的字母，以至于会多算。

所以可以开一个数组，统计字符个数，在计算时减掉。

不过每一次变换后要清零（被变换的字母要变成后面字母的个数）。

然后……就没有然后了，上代码：

```
#include<bits/stdc++.h>
using namespace std;
string s;long long ans;
long long num[201];
char ch;
int main(){
	cin>>s;
	num[int(s[s.length()-1])]++;
	num[int(s[s.length()-2])]++;
	for(int i=s.length()-3;i>=0;i--){
		num[int(s[i])]++;
		if(s[i]==s[i+1]&&s[i+2]!=s[i+1]){
			ans+=s.size()-i-num[s[i]];
			for(int j=int('a');j<=int('z');j++){
				num[j]=0;
			}
			num[int(s[i])]=(s.size()-i);
		}
	}
	cout<<ans;
	return 0;
}

```

感谢各位在评论区 $\tt hack$ 的大佬们~

---

## 作者：WaterSun (赞：0)

# 题意

给定一个字符串 $S$，你可以选择一个 $i(1 \leq i \leq |S|)$，如果 $s_i = s_{i + 1} \neq s_{i + 2}$，就将 $s_{i + 2}$ 设为 $s_i$。

问：最多能操作几次。

# 思路

我们可以用一个后缀和 $s_{i,j}$ 维护 $S_i \sim S_n$ 中与 $j$ 不同的数量。

然后，我们可以发现一个规律：我们的操作一定是从后往前操作最优。

那么我们对于每一次操作分类讨论一下（其中 $ln$ 表示上一次操作的位置）：

- 如果它是第一次操作，答案就加 $s_{i + 1,S_i}$。

- 如果它的 $s_i$ 为上一次操作的字符，答案就加上 $(s_{i + 1,S_i} - s_{ln,S_i}) + n - ln + 1$。

- 否则，答案加上 $s_{i + 1,S_i} - s_{ln,S_i}$。

# code

```cpp
#include <bits/stdc++.h>
#define int long long
#define re register

using namespace std;

const int N = 2e5 + 10;
int n,ln,ans;
int sum[N][124];
char lc;
string s;
//ln：上一次操作的位置
//lc：上一次操作的字符 

inline int read(){
	int r = 0,w = 1;
	char c = getchar();
	while (c < '0' || c > '9'){
		if (c == '-') w = -1;
		c = getchar();
	}
	while (c >= '0' && c <= '9'){
		r = (r << 3) + (r << 1) + (c ^ 48);
		c = getchar();
	}
	return r * w;
}

signed main(){
	ios::sync_with_stdio(0);
	cin.tie(0);
	cout.tie(0);
	cin >> s;
	n = s.length();
	s = ' ' + s;	
	for (re int i = n;i;i--){
		for (re int j = 'a';j <= 'z';j++) sum[i][j] = sum[i + 1][j] + 1;
		sum[i][s[i]]--;
	}
	for (re int i = n;i >= 1;){
		if (s[i] == s[i - 1]){//判断是否需要操作 
			if (!ln) ans += sum[i + 1][s[i]];//因为没有操作过，且不能选相同的，所以要加上 sum[i + 1][s[i]]
			else if (s[i] != lc) ans += (sum[i + 1][s[i]] - sum[ln][s[i]]) + n - ln + 1;//因为你从 ln ~ n 的位置都是为 lc(lc 不等于 s[i])，所以 lc ~ n 一定都能填上。但是不能直接加上 sum[i + 1][s[i]]，需要减去 lc ~ n 的那部分 
			else ans += sum[i + 1][s[i]] - sum[ln][s[i]];// ln ~ n 是填过的，所以要减去 
			ln = i - 1;//更新 
			lc = s[i];
			i -= 2;
		}
		else i--;
	}
	printf("%lld",ans);
	return 0;
}
```

---

