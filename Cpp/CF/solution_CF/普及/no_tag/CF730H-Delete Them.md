# Delete Them

## 题目描述

Polycarp is a beginner programmer. He is studying how to use a command line.

Polycarp faced the following problem. There are $ n $ files in a directory and he needs to delete some of them. Polycarp wants to run a single delete command with filename pattern as an argument. All the files to be deleted should match the pattern and all other files shouldn't match the pattern.

Polycarp doesn't know about an asterisk '\*', the only special character he knows is a question mark '?' which matches any single character. All other characters in the pattern match themselves only.

Formally, a pattern matches a filename if and only if they have equal lengths and all characters in the corresponding positions are equal except when the character in the pattern is '?', in which case the corresponding filename character does not matter.

For example, the filename pattern "a?ba?":

- matches filenames "aabaa", "abba.", "a.ba9" and "a.ba.";
- does not match filenames "aaba", "abaab", "aabaaa" and "aabaa.".

Help Polycarp find a pattern which matches files to be deleted and only them or report if there is no such pattern.

## 样例 #1

### 输入

```
3 2
ab
ac
cd
1 2
```

### 输出

```
Yes
a?
```

## 样例 #2

### 输入

```
5 3
test
tezt
test.
.est
tes.
1 4 5
```

### 输出

```
Yes
?es?
```

## 样例 #3

### 输入

```
4 4
a
b
c
dd
1 2 3 4
```

### 输出

```
No
```

## 样例 #4

### 输入

```
6 3
.svn
.git
....
...
..
.
1 2 3
```

### 输出

```
Yes
.???
```

# 题解

## 作者：YOKIMIYA (赞：3)

### 求目标串-->
暴力枚举m个字符串的每一位，与目标串当前位比较，若不同则改其为‘？’，否则不变。记其为$s$。

### 判断合法-->

与非m个字符串中的字符串比较，若存在一个位置，$s$与字符串在此位不相同且不为‘？'，可以判断不合法，输出 _No_ 即可。
否则在最后输出 _Yes_ 与$s$即可。


```cpp
#include<bits/stdc++.h>
using namespace std;
int n,m,ff;
int vis[105];
string s[105],ans;
void add(int i)
{
	if(ans.size()==0) ans=s[i];
    //若ans此时没有被赋值，则无脑将第一个赋给它
	else {
		int cnt=0;
		for(int j=0;j<ans.size();j++)
		if(j<s[i].size()) 
			if(ans[j]!=s[i][j]) ans[j]='?';
			//若ans这一位与s[i]不同，改其为‘？’
		if(ans.size()!=s[i].size()) {
			cout<<"No"<<endl;
			ff=1;
			return;
		}//若ans与s[i]长度不同，结束
	}
}
void check()
{
	for(int i=1;i<=n;i++) 
	if(!vis[i]) {
		if(ans.size()!=s[i].size()) continue;
        //小优化，如果ans与s[i]长度不相等，跳过
		int j=0,f=0;
		for(;j<ans.size();j++)
		if(ans[j]!=s[i][j] && ans[j]!='?') f=1;
       //若存在一位不为‘？’且不相同，标记一下
		if(f==1) continue; 
		cout<<"No"<<endl;
		return;
	}
	cout<<"Yes"<<endl<<ans<<endl;//输出
}
int main()
{
	cin>>n>>m;
	for(int i=1;i<=n;i++) cin>>s[i];
	for(int i=1;i<=m;i++) {
		int x; cin>>x;
		vis[x]=1;
	}
	for(int i=1;i<=n;i++)
	if(vis[i]) add(i);
	if(!ff)check();
}
```


---

## 作者：sto__Liyhzh__orz (赞：2)

这个题的翻译真的有点儿~~玄学~~。

[传送门：](https://www.luogu.com.cn/problem/CF730H)

题意：

让我们遍历 $m$ 个字符串的每一位，与目标串相比较，不同则改成 `?`，否则就不变。

记答案为 $ans$。

与其他非 $m$ 个字符串进行比较，若有一个位置，当且仅当 $ans$ 与字符串 $s_i$ 此位不同且不为 `?` ，可以推出不存在，输出 `No`。

最后输出 `Yes` 和 $ans$ 即可。

---

## 作者：GJX_Algorithm (赞：1)

# CF730H题解
## 1. 题意：

- 给定 $n$ 个字符串，要删除 $m$ 个字符串，新建一个字符串，$m$ 个字串的公共字符保留，其余为 ‘$?$’。

- 这个新字符串如果包含非删除的字符串，输出 No，否则输出 Yes 与新字符串。

## 2. 思路：

- 首先看数据范围：$1 \le m \le n \le 100$，纯暴力啊。

- 然后构造新字符串，注意删除的字符串长度不一定相等。

- 最后检查，逐位判断即可。

## 3. 代码：

```cpp
void build()
{
    for (int i = 2; i <= m; i++)
    {
        if (s[id[1]].size() != s[id[i]].size())
        {
            cout << "No";
            flag = 1;
            return ;
        }
        for (int j = 0; j < s[id[1]].size(); j++)
            if (s[id[i]][j] != s[id[1]][j])
                s[id[1]][j] = '?';
    }
    return ;
}
void check()
{
    for (int i = 1; i <= n; i++)
    {
        if (vis[i] == 1 || s[id[1]].size() != s[i].size()) continue; 
        int sum = 0;
        for (int j = 0; j < s[i].size(); j++)
            if (s[i][j] == s[id[1]][j] || s[id[1]][j] == '?') 
                sum++;
        if (sum == s[i].size()) 
        {
            cout << "No";
            flag = 1;
            return ;
        }
    }
    return ;
}
```

---

## 作者：Jerry_heng (赞：0)

就这么一道字符串练手题，调了我四次。

~~翻译挺玄学的。~~

其实题意很简单，过程如下。

1. 通过给定字符串求出 $ans$ 字符串，具体来讲就是如果相同位字符不同就用 $?$ 替代。

2. 再将 $ans$ 重新验证一遍，就是判断没被选中的能否用 $ans$ 匹配。 

```cpp
#include<bits/stdc++.h>
using namespace std;
int n,m,l;
string st[101],ans;
bool b,vis[101];
int main(){
	cin>>n>>m;
	for(int i=1;i<=n;i++)cin>>st[i];
	for(int i=1;i<=m;i++){
		int x;
		cin>>x;
		vis[x]=1;//标记
        	//ans记录答案，l记录长度
		if(!b)ans=st[x],l=st[x].length(),b=1;
		else{
			if(st[x].length()!=l){
				cout<<"No";
				return 0;
			}
			for(int j=0;j<l;j++)
				if(ans[j]!=st[x][j])ans[j]='?';//不匹配的那一位变为?
		}
	}
	for(int i=1;i<=n;i++){//判断ans能否取
		if(vis[i]||st[i].length()!=l)continue;
		b=0;
		for(int j=0;j<l;j++)
			if(st[i][j]!=ans[j]&&ans[j]!='?'){
				b=1;
				break;
			}//没被选中的也能匹配
		if(!b){
			cout<<"No";
			return 0;
		}
	}
	cout<<"Yes"<<endl;
	cout<<ans;
	return 0;
} 
```


---

## 作者：Awa486 (赞：0)

## ~~字符串练手题~~
需要注意原题要求**该匹配字符不能包含其他不能删除的字符串**

![image.png](https://i.loli.net/2019/08/23/9zhsBpGJj3tyKCe.png)
所以代码中应该加上~~判重语句~~
```cpp
for(i=1;i<=n;i++) {
		if(i == a[num])
			num++;//如果是已经被列入删除列表的，则跳过它
		else { //检查ans是否会与某一项相同
			if(strlen(s[i])!=len)//如果长度不同，剪枝
				continue;
			for(j=0; j<k; j++) {
				if(s[i][j]!=ans[j]&&ans[j]!='?')
                //判定该字符串是否与ans相同。一有不同即可跳出循环
					break;
			}
			if(j==k)
            //循环完还没有发现不同，说明有重复的字符串
				break;
		}
```



**明确这点之后直接模拟一波即可**

```cpp
#include<bits/stdc++.h>//万能头
using namespace std;
int main() {
	int n,m,num=0,a[200];
	char s[200][200],ans[200];
	cin>>n>>m;
	for(int i=1;i<=n;i++)
		cin>>s[i];//输入字符串
	for(int i=0;i<m;i++)
		cin>>a[i];//输入需操作的字符串序号
	int len = strlen(s[a[0]]);
	int i,j;
	for(i=1;i<m; i++) {
		int x= strlen(s[a[i]]);
		if(x!=len)//先检查，如果两字符串长度不同，则直接跳过
			break;
	}
	if(i != m) {
		cout<<"No";
		return 0;//输No滚粗
	}
	int k=0;
	for(i=0; i<len; i++) { //如果长度相同，开始操作
		char tmp= s[a[0]][i];//tmp存储第一个字符串的第i个字母
		for(j=1; j<m; j++) {
			char x = s[a[j]][i];//将tmp与其他字符串比对
			if(x !=tmp)
				break;//如果不对头就跳出循环
		}
		if(j != m)//如果还没比对完就跳出来说明第i项上有不同字母
			ans[k++] = '?';//输出'?'
		else
			ans[k++] =tmp;
	}
	ans[k] = '\0';

	for(i=1;i<=n;i++) {
		if(i == a[num])
			num++;//如果是已经被列入删除列表的，则跳过它
		else { //检查ans是否会与某一项相同
			if(strlen(s[i])!=len)//如果长度不同，剪枝
				continue;
			for(j=0; j<k; j++) {
				if(s[i][j]!=ans[j]&&ans[j]!='?')
                //判定该字符串是否与ans相同。一有不同即可跳出循环
					break;
			}
			if(j==k)
            //循环完还没有发现不同，说明有重复的字符串
				break;
		}
	}
	if(i!=n+1)//如果循环被中途跳出
		cout<<"No";//说明该方案不可行
	else 
		cout<<"Yes"<<endl<<ans;
	return 0;//完美结束
}
```


---

## 作者：__Creeper__ (赞：0)

~~字符串练手题~~

遍历 $m$ 个字符串的每一位，与目标串相比较，不同则改成 `?`，记其为 $ans$。

再将 $ans$ 重新验证一遍，就是判断没被选中的能否用 $ans$ 匹配。

## Code 

```cpp
#include <bits/stdc++.h>
#define X1 x1
#define X0 x0
#define Y1 y1
#define Y0 y0
#define int long long
using namespace std;

const int N = 105;
int n, m, a[N], l;
bool v;
string s[N], ans;
map<int, bool> mp;

void solve() {
	cin >> n >> m;
	for(int i = 1; i <= n; i++) {
		cin >> s[i];
	}
	for(int i = 1; i <= m; i++) {
		cin >> a[i];
		mp[a[i]] = 1;
		if(i == 1) ans = s[a[i]], l = s[a[i]].size();
		else {
			if(s[a[i]].size() != l) {
				cout << "No";
				return;
			}
			for(int j = 0; j < l; j++) {
				if(ans[j] != s[a[i]][j]) ans[j] = '?';
			}
		}
	}
	for(int i = 1; i <= n; i++) {
		if(mp[i] || s[i].size() != l) continue;
		v = 0;
		for(int j = 0; j < l; j++) {
			if(s[i][j] != ans[j] && ans[j] != '?') {
				v = 1;
				break;
			}
		}
		if(!v) {
			cout << "No";
			return;
		}
	}
	cout << "Yes\n" << ans;
}

signed main()
{
	ios::sync_with_stdio(0);
	cin.tie(0);
	cout.tie(0);
	int T = 1;
//	cin >> T;
	while (T--) solve();
	return 0;
}
```

---

