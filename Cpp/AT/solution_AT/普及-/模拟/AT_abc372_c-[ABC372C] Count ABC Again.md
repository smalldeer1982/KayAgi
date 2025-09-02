# [ABC372C] Count ABC Again

## 题目描述

给定一个长度为 $N$ 的字符串 $S$。接着给出 $Q$ 个查询，依次处理。

对于第 $i$ 个查询：

- 给定一个整数 $X_i$ 和一个字符 $C_i$，将 $S$ 的第 $X_i$ 个字符替换为 $C_i$。然后，输出字符串 $S$ 中包含 `ABC` 作为子串的次数。

这里，$S$ 的 **子串** 指的是，从 $S$ 的开头删除 $0$ 个或多个字符，从 $S$ 的结尾删除 $0$ 个或多个字符后得到的字符串。

例如，`ab` 是 `abc` 的子串，但 `ac` 不是 `abc` 的子串。

## 说明/提示

### 约束

- $3 \le N \le 2×10^5$
- $1 \le Q \le 2×10^5$
- $S$ 是由大写字母组成的长度为 $N$ 的字符串
- $1 \le Xi \le N$
- $C_i$ 是大写字母

### 示例解释 1

处理每个查询后的 $S$ 如下：

- 处理第 $1$ 个查询后：$S$ 变为 `ABCBABC`。其中 `ABC` 作为子串出现了 $2$ 次。
- 处理第 $2$ 个查询后：$S$ 变为 `ABABABC`。其中 `ABC` 作为子串出现了 $1$ 次。
- 处理第 $3$ 个查询后：$S$ 变为 `ABABCBC`。其中 `ABC` 作为子串出现了 $1$ 次。
- 处理第 $4$ 个查询后：$S$ 变为 `ABAGCBC`。其中 `ABC` 作为子串出现了 $0$ 次。

### 示例解释 2

有时处理查询前后 $S$ 可能不会发生变化。

## 样例 #1

### 输入

```
7 4
ABCDABC
4 B
3 A
5 C
4 G```

### 输出

```
2
1
1
0```

## 样例 #2

### 输入

```
3 3
ABC
1 A
2 B
3 C```

### 输出

```
1
1
1```

## 样例 #3

### 输入

```
15 10
BBCCBCACCBACACA
9 C
11 B
5 B
11 B
4 A
8 C
8 B
5 B
7 B
14 B```

### 输出

```
0
0
0
0
1
1
2
2
1
1```

# 题解

## 作者：DragonForge (赞：6)

# AT_abc372_c [ABC372C] Count ABC Again
[题目传送门](https://www.luogu.com.cn/problem/AT_abc372_c)

## 思路
由于题目中要求统计 `abc` 出现的次数，可能最先想到的是每一次从左往右遍历，如果出现了 `abc`，就把 `ans` 加一。
但是很显然这是不行的，毕竟 $3 \le N \le 2\times 10^5$，$1 \le Q \le 2 \times 10^5$。这时候我们注意到，当我们在修改一个字符的时候，受到影响的只有前面两个，后面两个以及他本身。所以在输入完字符后预处理 `abc` 的个数，而每次修改完再进行更新。代码很好实现。
### code
```cpp
#include <bits/stdc++.h>
using namespace std;
const int MAXN=2e5+10;
int n,q;
char s[MAXN];
int main(){
	cin>>n>>q;
	scanf("%s",s+1);
	int ans=0;
	for(int i=2;i<n;i++){
		if(s[i-1]=='A'&&s[i]=='B'&&s[i+1]=='C'){
			ans++;
		}
	}
	while(q--){
		int x;
		char c;
		cin>>x>>c;
		if(s[x]==c){
			cout<<ans<<endl;
			continue;
		}
		if(s[x-2]=='A'&&s[x-1]=='B'&&s[x]=='C'&&c!='C'){
			ans--;
		}
		if(s[x-1]=='A'&&s[x]=='B'&&s[x+1]=='C'&&c!='B'){
			ans--;
		}
		if(s[x]=='A'&&s[x+1]=='B'&&s[x+2]=='C'&&c!='A'){
			ans--;
		}
		
		if(s[x-2]=='A'&&s[x-1]=='B'&&s[x]!='C'&&c=='C'){
			ans++;
		}
		if(s[x-1]=='A'&&s[x]!='B'&&s[x+1]=='C'&&c=='B'){
			ans++;
		}
		if(s[x]!='A'&&s[x+1]=='B'&&s[x+2]=='C'&&c=='A'){
			ans++;
		}
		s[x]=c;
		cout<<ans<<endl;
	}
	return 0;
}
```
### 完结散花！

---

## 作者：cqsunny (赞：3)

当修改了第 $i$ 个字符，只对第 $i - 2$ 到 $i + 2$ 有影响。

因此先统计出开始时的 `abc` 个数，改变第 $i$ 个位置后，对上面的区间进行修改即可。


---

```cpp
#include<bits/stdc++.h>
using namespace std;
int n, q;
string s;
int sum = 0;
int main(){
    scanf("%d %d", &n, &q);
    cin >> s;
    //初始统计
    for(int i = 2; i < n; ++ i){
        if(s[i - 2] == 'A' && s[i - 1] == 'B' && s[i] == 'C'){
            ++ sum;
        }
    }
    while(q --){
        int x;
        char y;
        cin >> x >> y;
        -- x;
        if(s[x] == y){
            printf("%d\n", sum);
            continue;
        }
        //x - 2 到 x
        if(x >= 2 && s[x - 2] == 'A' && s[x - 1] == 'B' && s[x] == 'C'){
            -- sum;
        }
        //x - 1 到 x + 1
        else if(x >= 1 && x < n && s[x - 1] == 'A' && s[x] == 'B' && s[x + 1] == 'C'){
            -- sum;
        }
        //x 到 x + 2
        else if(x < n - 1 && s[x] == 'A' && s[x + 1] == 'B' && s[x + 2] == 'C'){
            -- sum;
        }
        s[x] = y;
        //修改后同理
        if(x >= 2 && s[x - 2] == 'A' && s[x - 1] == 'B' && s[x] == 'C'){
            ++ sum;
        }
        else if(x >= 1 && x < n && s[x - 1] == 'A' && s[x] == 'B' && s[x + 1] == 'C'){
            ++ sum;
        }
        else if(x < n - 1 && s[x] == 'A' && s[x + 1] == 'B' && s[x + 2] == 'C'){
            ++ sum;
        }
        printf("%d\n", sum);
    }
    return 0;
}
```

---

## 作者：Redamancy_Lydic (赞：3)

[博客内食用更佳](https://www.cnblogs.com/Lydic/p/18425187)

乍一看好像是数据结构。

我们结合题目所求内容考虑。对于每次修改，能对答案产生影响的最多只能是当前字符向前和向后延伸 $2$ 个元素所构成的长为 $5$ 的子串。

那么我们先 $\mathcal{O}(n)$ 计算出来初始答案。每次修改的时候，不妨先把 $i-2\sim i$ 和 $i-1\sim i+1$ 和 $i\sim i+2$ 这三个子串的贡献减去，然后直接修改元素，最后重新计算这三个子串的贡献即可。

对于贡献计算的话，因为下标边界的问题，我们可以写一个函数方便处理。如下：

```cpp
bool ch(int x)
{
	if(x<=0||x+2>n)return 0;
	return s[x]=='A'&&s[x+1]=='B'&&s[x+2]=='C';
}
```

[提交记录](https://atcoder.jp/contests/abc372/submissions/57966407)

---

## 作者：hjyowl (赞：2)

### 题目大意

给定你一个字符串 $s$，每次修改一个点，询问你修改后有多少个 ```ABC``` 的字串，修改不会撤销。

### 思路

很明显发现一个结论，就是修改了 $x$ 点，受到影响的只有以 $x$ 为中心的长度为 $5$ 的一端，因为只有这些地方才会受到影响。

所以说我们可以利用上一次的结果，如果对于这一段里的某一个字串，如果他以前是 ```ABC``` 但是现在不是了，那么就对答案减一。相反，如果他以前不是 ```ABC``` 但是现在是了，我们就加一。

所以说时间复杂度 $\Theta(n+q)$。

### 代码：

```cpp
#include <bits/stdc++.h>
using namespace std;
const int N = 1000010;
int a[N];
int main(){
	ios::sync_with_stdio(false);
	cin.tie(0),cout.tie(0);
	int n,q;
	cin >> n >> q;
	string s;
	cin >> s;
	int cnt =0 ;
	for (int i =0 ; i < s.size() - 2; i ++ ){
		if (s[i] == 'A' && s[i + 1] == 'B' && s[i + 2] == 'C'){
			cnt ++ ;
		}
	}
	while (q -- ){
		int t;
		cin >> t;
		char c;
		cin >> c;
		string x = s;
		s[t - 1] = c; 
		for (int i = max(t - 3,0); i < min(t,(int)s.size() - 2); i ++ ){
			if (s[i] == 'A' && s[i + 1] == 'B' && s[i + 2] == 'C' && !(x[i] == 'A' && x[i + 1] == 'B' && x[i + 2] == 'C')){
				cnt ++ ;
			}
			if (!(s[i] == 'A' && s[i + 1] == 'B' && s[i + 2] == 'C') && (x[i] == 'A' && x[i + 1] == 'B' && x[i + 2] == 'C')){
				cnt -- ;
			}
		}
		cout << cnt << endl;
	}
	return 0;
}
```

---

## 作者：Chenyanxi0829 (赞：2)

设 $f_i$ 表示字串 $s_i,s_{i+1},s_{i+2}$ 是否等于 `ABC`，那么就需要维护 $f_i(i\le n-2)$ 之和。每次又是单点修改，只会改变 $f_{i-2},f_{i-1},f_i$，所以可以每次都重新算一遍这三个值，但是要判一下这三个位置的 $f$ 是否存在。

## 代码
```cpp
#include <bits/stdc++.h>

using namespace std;

const int kMaxN = 2e5 + 1;

int n, q, ans;
char c;
bool f[kMaxN];
string s;

int main() {
  ios::sync_with_stdio(0), cin.tie(0);
  cin >> n >> q >> s;
  for (int i = 1; i + 2 <= n; i++) {
    ans += (f[i] = s.substr(i - 1, 3) == "ABC");
  }
  for (int i = 1, x; i <= q; i++) {
    cin >> x >> c, s[x - 1] = c;
    x >= 3 && (ans -= f[x - 2], ans += (f[x - 2] = s.substr(x - 3, 3) == "ABC"));
    x >= 2 && x < n && (ans -= f[x - 1], ans += (f[x - 1] = s.substr(x - 2, 3) == "ABC"));
    x + 1 < n && (ans -= f[x], ans += (f[x] = s.substr(x - 1, 3) == "ABC"));
    cout << ans << '\n';
  }
  return 0;
}
```

---

## 作者：sherry_lover (赞：1)

# AT_abc372_c [ABC372C] Count ABC Again 题解

[题目传送门](https://www.luogu.com.cn/problem/AT_abc372_c)

## 思路

我们注意到每次修改只跟包含这个字母的子段有关系，所以每次修改先删掉包含这个字母的子段的答案，然后修改字符串，再加上包含这个字母的子段的答案即可。注意边界条件。

Code：
```cpp
#include<bits/stdc++.h>
using namespace std;
int n,q,ans;
string s;
bool check(int l,int r)
{
	if(l < 1 || r > n) return false;
	return (s[l] == 'A' && s[l+1] == 'B' && s[l+2] == 'C');
}
int main()
{
	cin >> n >> q >> s;
	s = " " + s;
	for(int i = 1;i <= n-2;i++) ans += check(i,i+2);
	while(q--)
	{
		int x;
		char c;
		cin >> x >> c;
		ans -= (check(x-2,x)+check(x-1,x+1)+check(x,x+2));
		s[x] = c;
		ans += (check(x-2,x)+check(x-1,x+1)+check(x,x+2));	
		cout << ans << endl;
	}
	return 0;
}
```

---

## 作者：cjh_trailblazer (赞：1)

[at原题面](https://atcoder.jp/contests/abc372/tasks/abc372_c)
## 题意简述：
给一个长为 $n$ 的字符串 $s$，$q$ 次询问，每次将第 $x$ 位上的字符修改为 $c$。每次询问后，输出串 $s$ 中有几个子串为 ABC。($n ,q\le2\times10^5$)
## 题目分析：
注意到数据范围，可以直接暴力模拟跑线性，但修改后别重复扫串。

我们可以输入串时直接统计答案，对于单次修改的位置进行判断，删去该字符后，若有 ABC 的结构被破坏，则令答案减一，填上修改后的字符后若有 ABC 的结构建立，则令答案加一。  
因此对于单次询问只需进行六次判断即可，复杂度接近线性。
## 代码如下：
```cpp
#include<bits/stdc++.h>
#define starrail main
#define int long long
#define lowbit(x)  (x&(-x))
#define re register
using namespace std;
inline int read(){
	int w=1,s=0;char ch=getchar();
	while(!isdigit(ch)){if(ch=='-') w=-1;ch=getchar();}
	while(isdigit(ch)){s=s*10+(ch-'0');ch=getchar();}
	return w*s;
}
int n,q,t=0;
string s;
signed starrail()
{
    n=read();q=read();
    cin>>s;
    s=' '+s;
    for(int i=1;i<=n;i++) 
        if(s[i]=='A'&&s[i+1]=='B'&&s[i+2]=='C') t++;
    while(q--){
        int i;
        char c;
        cin>>i>>c;
        if(s[i]=='A'&&s[i+1]=='B'&&s[i+2]=='C')
            if(c!='A') t--;
        if(s[i-1]=='A'&&s[i]=='B'&&s[i+1]=='C')
            if(c!='B') t--;
        if(s[i-2]=='A'&&s[i-1]=='B'&&s[i]=='C')
            if(c!='C') t--;
        if(c=='A'&&s[i]!='A'&&s[i+1]=='B'&&s[i+2]=='C') 
            t++;
        if(s[i-1]=='A'&&c=='B'&&s[i]!='B'&&s[i+1]=='C')
            t++;
        if(s[i-2]=='A'&&s[i-1]=='B'&&c=='C'&&s[i]!='C')
            t++;
        s[i]=c;
        printf("%lld\n",t);
    }
	return 0;
}


```

---

## 作者：Malkin_Moonlight (赞：1)

# 题解：AT_abc372_c [ABC372C] Count ABC Again

如果忽略约束，可以这样解决：

- 将字符串 $S$ 的第 $X_i$ 个字符修改为 $C_i$。
- 检查字符串 $S$ 中 $(N-2)$ 个长度为 3 的子串，查看每个子串是否与 `ABC` 匹配，并打印这样的子串数量。

然而，$N$ 和 $Q$ 可以达到 $2 \times 10^5$，因此这个解决方案会导致超时。

现在注意到，修改 $S$ 中的一个字符最多会改变三个长度为 3 的子串。

例如，假设 $S = \text{ABCDEFGHI}$，修改后变为 $S = \text{ABCZEFGI}$。在修改之前，$S$ 的长度为 $3$ 的子串为：

- `ABC`，`BCD`，`CDE`，`DEF`，`EFG`，`FGH`，`GHI`。

修改后变为：

- `ABC`，`BCZ`，`CZE`，`ZEF`，`EFG`，`FGH`，`GHI`。

在这些子串中，只有三个发生了变化。一般来说，最多会有三个长度为 3 的子串会改变。

因此，只需检查可能变化的三个子串，计算修改前后 `ABC` 的数量，并根据差异和修改前的计数找到修改后的答案即可。

时间复杂度 $O(N + Q)$。

---

## 作者：hzxphy (赞：1)

## 题目大意
给定一个字符串 $S[1,\dots,n]$，有 $Q$ 次询问，每一次查询修改一个字符，问每一次修改完后有多少个字串 ```ABC```？
## 思路
我们可以发现，一次修改最多加上 $3$ 至 $-3$ 个字串。所以考虑维护由每个节点为开头是否为 ```ABC``` 的值。

随后动态维护 $flag_x,flag_{x-1},flag_{x-2}$ 的数量。
## Code
```cpp
#include<bits/stdc++.h>
using namespace std;
const int MAXN=2e5;
int n,q;
string s;
bool flag[MAXN];
int main(){
    cin>>n>>q>>s;
    int sum=0;
    for(int i=0;i<(int)s.size();i++){
        if(i<=(int)s.size()-3&&(s.substr(i,3)=="ABC")){
            flag[i]=true;sum++;
        }
    }
    while(q--){
        int x;char c;
        cin>>x>>c;x--;
        s[x]=c;
        if(flag[x]&&(s.substr(x,3)!="ABC")){
            flag[x]=false;sum--;
        }
        else if(!flag[x]&&(s.substr(x,3)=="ABC")){
            flag[x]=true;sum++;
        }
        if(x>=1&&flag[x-1]&&(s.substr(x-1,3)!="ABC")){
            flag[x-1]=false;sum--;
        }
        else if(x>=1&&!flag[x-1]&&(s.substr(x-1,3)=="ABC")){
            flag[x-1]=true;sum++;
        }
        if(x>=2&&flag[x-2]&&(s.substr(x-2,3)!="ABC")){
            flag[x-2]=false;sum--;
        }
        else if(x>=2&&!flag[x-2]&&(s.substr(x-2,3)=="ABC")){
            flag[x-2]=true;sum++;
        }
//        cout<<s<<' '<<flag[x]<<'\n';
        cout<<sum<<'\n';
    }
    return 0;
}
```

---

## 作者：__Creeper__ (赞：1)

### 思路

很简单的模拟题，每次操作前先把 $[x - 2, x]$，$[x - 1, x + 1]$，$[x, x + 2]$ 的答案删掉，再在修改后重新统计上述区间的答案，输出即可。

### Code

```cpp
#include <bits/stdc++.h>
using namespace std;

int main()
{
	ios::sync_with_stdio(0);
	cin.tie(0);
	cout.tie(0);
	int n, m, cnt = 0;
	string s;
	cin >> n >> m >> s;
	s = " " + s + "        ";
	for ( int i = 1; i <= n - 2; i++ )
	{
		if ( s[i] == 'A' && s[i + 1] == 'B' && s[i + 2] == 'C' ) cnt++;
	}
	while ( m-- )
	{
		int x;
		char c;
		cin >> x >> c;
		for ( int i = 0; i <= 2; i++ )
		{
			if ( x - i <= 0 ) continue;
			if ( s[x - i] == 'A' && s[x - i + 1] == 'B' && s[x - i + 2] == 'C' ) cnt--;
		}
		s[x] = c;
		for ( int i = 0; i <= 2; i++ )
		{
			if ( x - i <= 0 ) continue;
			if ( s[x - i] == 'A' && s[x - i + 1] == 'B' && s[x - i + 2] == 'C' ) cnt++;
		}
		cout << cnt << '\n';
	}
	return 0;
}
```

---

## 作者：small_lemon_qwq (赞：1)

记录字符串中下标为 $i$ 是否满足字符串 $[i,i+2]$ 为 `ABC`，设为 $f_i$，显然每次修改下标为 $x$ 的查询，只会让第 $f_{x-2},f_{x-1},f_x$ 的值改变，重新算答案即可。

```cpp
#include<bits/stdc++.h>
using namespace std;
#define int long long
int n,q,flag[200005],ans;
string s;
void update(int i){
	if(i+2>n)return;
	flag[i]=0;
	if(s[i]=='A'&&s[i+1]=='B'&&s[i+2]=='C'){
		flag[i]=1;
	}
}
signed main(){
	ios::sync_with_stdio(0);
	cin.tie(0);cout.tie(0);
	cin>>n>>q>>s;
	s=" "+s;
	for(int i=1;i<=n;i++){
		update(i);
		ans+=flag[i];
	}
	while(q--){
		int x;
		char c;
		cin>>x>>c;
		ans-=flag[x-1]+flag[x-2]+flag[x];
		s[x]=c;
		update(x-1);
		update(x-2);
		update(x);
		ans+=flag[x-1]+flag[x-2]+flag[x];
		cout<<ans<<"\n";
	}
	return 0;
}
```

---

## 作者：Your_Name (赞：0)

## 题意
给一个长度为 $N$ 字符串 $S$，有 $m$ 次操作，每次把 $S$ 的第 $X_i$ 个字符改为 $C$，并输出有多少个子串 `ABC`。
## 思路
由于每个 `ABC` 不会有交集，所以直接存下来当前这一位对答案有没有贡献。

修改时如果当前这位有贡献有就减掉，然后把剩下两位（`ABC` 除掉当前字母）的贡献标记也抹掉。

但还要考虑新增的贡献。

能产生新贡献的方法只有用新字母和老字母凑出 `ABC`，分类讨论即可。注意加上答案后还要记得把贡献标记打上。
## AC_Code

```cpp
#include<bits/stdc++.h>
using namespace std;
const int N = 2e5 + 10;
int n, m, ans;
bool vis[N];//贡献标记
string s;
int main(){
    cin >> n >> m >> s;
    for(int i = 0; i < s.size(); i ++){
        if(s[i] == 'A' && s[i + 1] == 'B' && s[i + 2] == 'C'){
            ans ++;//初始答案
            vis[i] = vis[i + 1] = vis[i + 2] = 1;//打上贡献标记
        }
    }
    while(m --){
        int x;
        char c;
        cin >> x >> c;
        x --;//string里从0开始
        if(vis[x]){
            ans --;
            if(s[x] == 'A'){
                vis[x] = vis[x + 1] = vis[x + 2] = 0;
            }else if(s[x] == 'B'){
                vis[x] = vis[x - 1] = vis[x + 1] = 0;
            }else if(s[x] == 'C'){
                vis[x] = vis[x - 2] = vis[x - 1] = 0;
            }
        }//去掉原有贡献
        if(c == 'A' && s[x + 1] == 'B' && s[x + 2] == 'C'){
            ans ++;
            vis[x] = vis[x + 1] = vis[x + 2] = 1;
        }else if(c == 'B' && s[x - 1] == 'A' && s[x + 1] == 'C'){
            ans ++;
            vis[x] = vis[x - 1] = vis[x + 1] = 1;
        }else if(c == 'C' && s[x - 2] == 'A' && s[x - 1] == 'B'){
            ans ++;
            vis[x] = vis[x - 2] = vis[x - 1] = 1;
        }//加上新的贡献
        s[x] = c;//记得改
        cout << ans << endl;
    }
    return 0;
}
```
 _完结撒花_

---

## 作者：Scean_Tong (赞：0)

## AT_abc372_C 题解

### 思路

先考虑这样一个问题，如何判断以 $i$ 开头的子串是否是 `ABC`。

显然只需要 $O(1)$ 判断 $s_i$ 是否为 `A`，$s_{i+1}$ 是否为 `B`，$s_{i+2}$ 是否为 `C`，能想到这里应该就能切这题了。

令 $f(i)$ 表示以 $i$ 开头的长度为 $3$ 的子串是否为 `ABC`，查询之前先算一遍对于 $s$ 的每一个 $i$ 的 $f(i)$，初始答案就是这些加起来。

对于每次操作，因为是单点改，所以只会影响三位的答案，所以只需要先将答案减去这三位的 $f(i)$，然后将 $s_x$ 改为 $c$，再将答案加上这三位的 $f(i)$ 即可，时间复杂度 $O(n+q)$。

### 代码实现

```cpp
#include<bits/stdc++.h>
#define int long long
using namespace std;
int T=1;
int n,q;
string s;
int ans=0;
const int maxn=2e5+7;
bool check(int i){
	return s[i]=='A'&&s[i+1]=='B'&&s[i+2]=='C';
}
void solve(){
	cin>>n>>q;
	cin>>s;
	s='#'+s;
	for(int i=1;i<=n;i++){
		ans+=check(i);
	}
	while(q--){
		int x;
		char c;
		cin>>x>>c;
		for(int i=x-2;i<=x;i++){
			ans-=check(i);
		}
		s[x]=c;
		for(int i=x-2;i<=x;i++){
			ans+=check(i);
		}
		cout<<ans<<'\n';
	}
}
int32_t main(){
	ios::sync_with_stdio(0);
	cin.tie(0),cout.tie(0);
//	cin>>T;
	while(T--){
		solve();
	}
	return 0;
}



```

---

## 作者：P_VICVIC_R (赞：0)

~~简单题~~

----

### 题意：

给一个长度为 $N$ 字符串 $S$，有 $m$ 次操作，每次把 $S$ 的第 $X_i$ 个字符改为 $C$，并输出有多少个子串 $\texttt{ABC}$。

### 思路：

可以先 $O(n)$ 把 $\texttt{ABC}$ 的数量全部先统计出来。

我们发现对于一个修改，只对 $S_{x_i-2}$ 到 $S_{X_i+2}$ 的几个串有影响，那么就可以直接暴力统计有影响的这几个串，直接在上一次的答案上修改就行了。

### code:

```c++
#include <bits/stdc++.h>
#define int long long 
using namespace std;
static const int N=1e6+5e5;
int n,m;
string s;
signed main(){
	std::cin.tie(nullptr)->sync_with_stdio(false);
	std::cout.tie(nullptr)->sync_with_stdio(false);
	cin>>n>>m;
	cin>>s;
	s=' '+s;
	int ans=0;
	for(int i=1;i<=n;i++){
		if(s[i]=='A' and s[i+1]=='B' and s[i+2]=='C')
			ans++;
	}
	while(m--){
		int op;
		char c;
		cin>>op>>c;
		int P=0,p=0;
		for(int i=op-2;i<=op+2;i++)
			if(s[i]=='A' and s[i+1]=='B' and s[i+2]=='C')
				P++;
		s[op]=c;
		for(int i=op-2;i<=op+2;i++)
			if(s[i]=='A' and s[i+1]=='B' and s[i+2]=='C')
				p++;
//		cout<<s<<'\n';
		ans-=P;
		ans+=p;
		cout<<ans<<'\n';
	}
	return 0;
}
```

---

