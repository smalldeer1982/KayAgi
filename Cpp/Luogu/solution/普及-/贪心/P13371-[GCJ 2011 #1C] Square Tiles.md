# [GCJ 2011 #1C] Square Tiles

## 题目描述

你正在出售美丽的几何画作。每幅画由 $1\times 1$ 的方块瓷砖组成，排列成不重叠的网格。例如：

```
    .##..
    .####
    .####
    .##..
```

蓝色瓷砖用字符 '#' 表示，白色瓷砖用字符 '.' 表示。你不会使用其他颜色。

但并不是每个人都喜欢蓝色，有些顾客希望你把画中的所有蓝色瓷砖都换成红色瓷砖。不幸的是，红色瓷砖只能是更大的 $2\times 2$ 尺寸，这让事情变得棘手。

你可以用一块红色瓷砖覆盖任意一个 $2\times 2$ 的蓝色瓷砖区域，然后重复此操作直到完成。红色瓷砖不能重叠，不能覆盖白色瓷砖，也不能超出画作边界。例如，你可以如下方式在上面的画作中添加红色瓷砖：

```
    ./\..
    .\//\
    ./\\/
    .\/..
```

每块红色瓷砖用左上和右下角的 '/' 字符，以及另外两个角的 '\\' 字符表示。

给定一幅蓝白画作，你能否用这种方式将其转换为红白画作？

## 说明/提示

**数据范围**

**小数据集（10 分，测试集 1 - 可见）**

- $1 \leq T \leq 20$。
- $1 \leq R \leq 6$。
- $1 \leq C \leq 6$。
- 时间限制：~~30~~ 3 秒。

**大数据集（10 分，测试集 2 - 隐藏）**

- $1 \leq T \leq 50$。
- $1 \leq R \leq 50$。
- $1 \leq C \leq 50$。
- 时间限制：~~60~~ 6 秒。

由 ChatGPT 4.1 翻译

## 样例 #1

### 输入

```
3
2 3
###
###
1 1
.
4 5
.##..
.####
.####
.##..```

### 输出

```
Case #1:
Impossible
Case #2:
.
Case #3:
./\..
.\//\
./\\/
.\/..```

# 题解

## 作者：ggpw_XNW (赞：7)

模拟题。  
其实题目就是让你把 $4$ 个`#`用`\/`代替。因为只是一个 $2 \times 2$ 的矩阵所以直接判断即可。如果满足条件就替换，否则就是无解。  
注意这里的反斜杠要用`(char)92`代替，因为平时反斜杠后面都带了一个字符。当然如果直接用`\`代替也没问题，只是麻烦一点。  
注意边界。
### code
```cpp
#include<iostream>
using namespace std;
char a[55][55];
int T , n , m;
int main(){
    cin >> T;
    for(int k=1;k<=T;k++){
        cin >> n >> m;
        for(int i=1;i<=n;i++){
            for(int j=1;j<=m;j++)cin >> a[i][j];
        }
        bool fl = 0;
        for(int i=1;i<n;i++){
            for(int j=1;j<m;j++){
                if(a[i][j]=='#'&&a[i+1][j]=='#'&&a[i][j+1]=='#'&&a[i+1][j+1]=='#'){
                    a[i][j] = a[i+1][j+1] = '/';
                    a[i+1][j] = a[i][j+1] = (char)92;
                }
            }
        }
        for(int i=1;i<=n;i++){
            for(int j=1;j<=m;j++){
                if(a[i][j]=='#'){
                    fl = 1;break;
                }
            }
            if(fl)break;
        }
        cout << "Case #" << k << ":\n";
        if(fl)cout << "Impossible\n";
        else{
            for(int i=1;i<=n;i++){
                for(int j=1;j<=m;j++)cout << a[i][j];
                cout << "\n";
            }
        }
    }
    return 0;
}
```

---

## 作者：Ghosty_Neutrino (赞：4)

## 题意
要求将由蓝色瓷砖 `#` 和白色瓷砖 `.` 组成的网格图片，用 $2 \times 2$ 的红色瓷砖替换所有蓝色瓷砖。替换需满足以下条件：
 
* 红色瓷砖不可重叠。

* 红色瓷砖不可覆盖白色瓷砖。

* 红色瓷砖不可超出图片范围。
 
输入包含多个测试用例，每个测试用例给出网格的行数 $R$ 和列数 $C$，以及网格内容。对于每个测试用例，若能完成替换则输出转换后的网格，否则输出 `Impossible` 。
## 分析
所有蓝色瓷砖必须被 $2 \times 2$ 的红色瓷砖完全覆盖，即每个 `#` 都需属于某个 $2 \times 2$ 的 `#` 区域。

这些 $2 \times 2$ 的 `#` 区域不能重叠，且必须完全位于网格内，也就是不能超出边界，同时不能包含白色瓷砖。

首先遍历网格中的每个位置 $(i,j)$，当遇到未被覆盖的 `#` 时，尝试以其为左上角放 $2 \times 2$ 红色瓷砖。

放置前需检查：
- 边界条件：确保 $i+1 < R$ 且 $j+1 < C$，即 $2 \times 2$ 区域完全在网格内。
- 区域有效性：该 $2 \times 2$ 区域内的四个位置均为 `#` 且未被覆盖。

若满足条件，则标记这四个位置为已覆盖，并记录红色瓷砖的位置；若不满足，则判定为 `Impossible`。

遍历结束后，需再次检查所有 `#` 是否均被覆盖，若有未覆盖的 `#`，则判定为 `Impossible`。
## 代码

```cpp
#include <bits/stdc++.h>
using namespace std;
int main() {
    int T;
    cin >> T;
    for (int t = 1; t <=T ; t++) {
        int R, C;
        cin >> R >> C;
        vector<string> g(R);
        for (int i = 0; i < R; i++) {
            cin >> g[i];
        }
        vector<vector<bool>> cov(R, vector<bool>(C, false));
        vector<string> res(R, string(C, '.'));
        bool f = true;
        for (int i = 0; i < R && f; i++) {
            for (int j = 0; j < C && f; j++) {
                if (g[i][j] == '#' && !cov[i][j]) {
                    if (i + 1 >= R || j + 1 >= C) {
                        f = false;
                        break;
                    }
                    if (g[i][j+1] != '#' || g[i+1][j] != '#' || g[i+1][j+1] != '#') {
                        f = false;
                        break;
                    }
                    if (cov[i][j+1] || cov[i+1][j] || cov[i+1][j+1]) {
                        f = false;
                        break;
                    }
                    cov[i][j] = cov[i][j+1] = cov[i+1][j] = cov[i+1][j+1] = true;
                    res[i][j] = '/';
                    res[i][j+1] = '\\';
                    res[i+1][j] = '\\';
                    res[i+1][j+1] = '/';
                }
            }
        }

        if (f) {
            for (int i = 0; i < R && f; i++) {
                for (int j = 0; j < C && f; j++) {
                    if (g[i][j] == '#' && !cov[i][j]) {
                        f = false;
                    }
                }
            }
        }

        cout << "Case #" << t << ":" << endl;
        if (f) {
            for (const string& r : res) {
                cout << r << endl;
            }
        } else {
            cout << "Impossible" << endl;
        }
    }
    return 0;
}

```

---

## 作者：qkj_qwq (赞：3)

# 解题思路
模拟。

先遍历所有字符，试着把所有 $2\times2$ 的蓝色瓷砖都替换成 $2\times2$ 的红色瓷砖。

若模拟铺完瓷砖之后，还有 `#` 剩余，则说明方案不成功，输出 `Impossible`。否则，全部蓝色瓷砖都替换成了红色瓷砖，输出模拟好的图即可。
## Code
```cpp
#include<bits/stdc++.h>
#define int long long
using namespace std;
char a[114][514];
signed main()
{
	ios::sync_with_stdio(0);
	cin.tie(0);
	cout.tie(0);
	int t;
	cin>>t;
	for(int tt=1;tt<=t;tt++)
	{
		cout<<"Case #"<<tt<<":\n";
		int n,m,f=0;
		cin>>n>>m;
		for(int i=1;i<=n;i++)
			cin>>a[i]+1;
		for(int i=1;i<=n;i++)
			for(int j=1;j<=m;j++)
				if(a[i][j]=='#')
					if(a[i+1][j]=='#'&&a[i][j+1]=='#'&&a[i+1][j+1]=='#')a[i][j]=a[i+1][j+1]='/',a[i][j+1]=a[i+1][j]='\\';
					else f=1;
		if(f)cout<<"Impossible\n";
		else for(int i=1;i<=n;i++)cout<<a[i]+1<<'\n';
	}
	return 0;
}
```

---

## 作者：LiJunze0501 (赞：3)

# 题目翻译（将就着看）
[题目翻译](https://www.luogu.com.cn/paste/2px7a2oa)。
# 分析
遍历这张图，遇到 `#`，就判断左、下、左下是否也为 `#`。  
如果符合，就将这一块变为“红地砖”。
```cpp

for(int i=1;i<=n;i++)
    for(int j=1;j<=m;j++)
        if(mp[i][j]=='#'&&mp[i+1][j]=='#'&&mp[i][j+1]=='#'&&mp[i+1][j+1]=='#'){
            mp[i][j]='/';
            mp[i][j+1]='\\';//如果要写 \ 这个字符，得写成 '\\'
            mp[i+1][j]='\\';
            mp[i+1][j+1]='/';
        }
```
再判断有没有剩余 `#`，有的话输出 `Impossible`，否则将处理好的图输出。
# Code

```cpp
#include<bits/stdc++.h>
using namespace std;
int t,n,m;
char mp[55][55];
int main(){
    ios::sync_with_stdio(0);
    cin.tie(0); cout.tie(0);
    cin>>t;
    for(int cas=1;cas<=t;cas++){
        cout<<"Case #"<<cas<<":\n";
        cin>>n>>m;
        for(int i=1;i<=n;i++)
            for(int j=1;j<=m;j++)
                cin>>mp[i][j];
        for(int i=1;i<=n;i++)
            for(int j=1;j<=m;j++)
                if(mp[i][j]=='#'&&mp[i+1][j]=='#'&&mp[i][j+1]=='#'&&mp[i+1][j+1]=='#'){
                    mp[i][j]='/';
                    mp[i][j+1]='\\';
                    mp[i+1][j]='\\';
                    mp[i+1][j+1]='/';
                }
        bool pos=true;
        for(int i=1;i<=n;i++)
            for(int j=1;j<=m;j++)
                if(mp[i][j]=='#'){
                    pos=false;
                    break;
                }
        if(pos){
            for(int i=1;i<=n;i++){
                for(int j=1;j<=m;j++) cout<<mp[i][j];
                cout<<"\n";
            }
        }
        else cout<<"Impossible\n";
    }
}
```

---

## 作者：Temp113 (赞：3)

## Solution

枚举 $i,j$，若当前为 ``#`` 字符，则将其视为左上角，并遍历四个位置，不满足要求输出 ``Impossible``，否则将其替换。

## Code

```cpp
#include<bits/stdc++.h>
using namespace std;
const int N = 55;
int t, n, m;
int dx[5] = {0, 0, 0, 1, 1}, dy[5] = {0, 0, 1, 0, 1}, nx, ny;
char s[N][N], ans[5] = {'*', '/', '\\', '\\', '/'};
inline void solve(){
	cin >> n >> m;
	for(int i = 1; i <= n; i++) for(int j = 1; j <= m; j++) cin >> s[i][j];
	for(int i = 1; i <= n; i++){
		for(int j = 1; j <= m; j++){
			if(s[i][j] != '#') continue;
			for(int k = 1; k <= 4; k++){
				nx = i + dx[k];
				ny = j + dy[k];
				if(nx > n || ny > m || s[nx][ny] != '#'){
					cout << "Impossible\n";
					return ;
				}
				s[nx][ny] = ans[k];
			}
		}
	}
	for(int i = 1; i <= n; i++){
		for(int j = 1; j <= m; j++) cout << s[i][j];
		cout << '\n';
	}
	return ;
}
int main(){
	ios::sync_with_stdio(false);
	cin.tie(nullptr);
	cin >> t;
	for(int kk = 1; kk <= t; kk++){
		cout << "Case #" << kk << ":\n";
		solve();
	}
	return 0;
}
```

---

## 作者：ziyaojia (赞：2)

这道题是一道简单的模拟题。

我们可以通过一个循环来枚举每个点当红色瓷砖的左上角的可能性，因为我想要用的红色瓷砖数最小，所以我们尽量让红色瓷砖覆盖的蓝色瓷砖数更多（最好全都是蓝色瓷砖）。

循环完之后判断还有没有蓝色瓷砖，如果有就输出  `Impossible`，否则就输出更改之后的图形。

注意：反斜杠要用`char(92)`表示。

然后就可以根据思路写出代码了。

### [AC](https://www.luogu.com.cn/record/225934352) Code:

```cpp
#include<bits/stdc++.h>
using namespace std;
int T,n,m;
char a[51][51];
int main(){
    cin>>T;
    for(int i=1;i<=T;i++){
        memset(a,'\0',sizeof(a));
        cin>>n>>m;
        for(int i=1;i<=n;i++)
            for(int j=1;j<=m;j++)
                cin>>a[i][j];
        for(int ii=1;ii<n;ii++)
            for(int j=1;j<m;j++){
                if(a[ii][j]=='#'&&a[ii+1][j]=='#'&&a[ii][j+1]=='#'&&a[ii+1][j+1]=='#'){
                    a[ii][j]=a[ii+1][j+1]='/';
                    a[ii+1][j]=a[ii][j+1]=(char)92;
                }
            }
        int flag=0;
        cout<<"Case #"<<i<<":\n";
        for(int ii=1;ii<=n;ii++){
            for(int j=1;j<=m;j++)
                if(a[ii][j]=='#'){
                    cout<<"Impossible"<<endl;
                    flag=1;
                    break;
                }
            if(flag)break;
        }
        if(flag)continue;
        for(int ii=1;ii<=n;ii++){
            for(int j=1;j<=m;j++)
                cout<<a[ii][j];
            cout<<endl;
        }
    }
    return 0;
}
```

---

## 作者：wanghaotian0227 (赞：2)

# P13371 题解
## 题意
一道很水的橙题。题目要求我们把 $2 \times 2$ 的 `#`字符替换成一对`/`字符和一对`\`字符。
## 程序
由于`.`也就是白色瓷砖没有什么实际作用，所以我们可以把它忽略掉，只考虑`#`。可以写两个循环来暴力搜索 $2 \times 2$ 的方格（枚举左上角的位置，注意下标不要超出数组范围），如果有 $2 \times 2$ 的由`#`组成的方格，就把它替换成`\`和`/`。
```cpp
for(int i=1;i<=r-1;i++)
	{
		for(int j=1;j<=c-1;j++)
		{
			if(p[i][j]=='#'&&p[i+1][j]=='#'&&p[i][j+1]=='#'&&p[i+1][j+1]=='#')
			{
				p[i][j]='/';p[i+1][j]='\\';p[i][j+1]='\\';p[i+1][j+1]='/';
			}
		}
	}
```
替换完成后需要加特判，判断是否达成要求。题目要求把所有的`#`替换掉，也就是说最终的图案中不能包含`#`。如果包含`#`就输出`Impossible`。如果不包含就输出图案。
```cpp
for(int i=1;i<=r;i++)
	{
		for(int j=1;j<=c;j++)
		{
			if(p[i][j]=='#')
			{
				cout<<"Case #"<<t<<":"<<endl;
				cout<<"Impossible"<<endl;
				return;
			}
		}
	}
	cout<<"Case #"<<t<<":"<<endl;
	for(int i=1;i<=r;i++)
	{
		for(int j=1;j<=c;j++)
		{
			cout<<p[i][j];
		}
		cout<<endl;
	}
```
时间复杂度为 $O(rc)$，不过看到 $1 \le r,c \le 50$ 的样例和 $6s$ 的时间限制，只能说还是太小看我们 OIer 了。

~~蒟蒻作者写题时看错下标了...~~
## 代码
```cpp
#include <iostream>
#include <string>
using namespace std;
int t;char p[114][514];//很臭的定义...
string s;
void solve()
{
	int r,c;
	cin>>r>>c;
	for(int i=1;i<=r;i++)
	{
		cin>>s;
		for(int j=1;j<=c;j++)
		{
			p[i][j]=s[j-1];//一定要注意string类型下标从0开始
		}
	}
	for(int i=1;i<=r-1;i++)
	{
		for(int j=1;j<=c-1;j++)
		{
			if(p[i][j]=='#'&&p[i+1][j]=='#'&&p[i][j+1]=='#'&&p[i+1][j+1]=='#')//特判
			{
				p[i][j]='/';p[i+1][j]='\\';p[i][j+1]='\\';p[i+1][j+1]='/';//反斜杠一定要加两个，要不然会编译错误
			}
		}
	}
	for(int i=1;i<=r;i++)
	{
		for(int j=1;j<=c;j++)
		{
			if(p[i][j]=='#')//如果出现一个蓝色就输出不可能
			{
				cout<<"Case #"<<t<<":"<<endl;
				cout<<"Impossible"<<endl;
				return;
			}
		}
	}
	cout<<"Case #"<<t<<":"<<endl;
	for(int i=1;i<=r;i++)
	{
		for(int j=1;j<=c;j++)
		{
			cout<<p[i][j];
		}
		cout<<endl;
	}
}
int main()
{
	int T;
	cin>>T;
	for(t=1;t<=T;t++)
	{
		solve();
	}
	return 0;//好习惯
}
```

---

## 作者：lailai0916 (赞：2)

## 原题链接

- [P13371 [GCJ 2011 #1C] Square Tiles](https://www.luogu.com.cn/problem/P13371)

## 题意简述

给定一个 $r\times c$ 的矩形区域，其中蓝色部分用 `#` 表示。判断是否能用不重叠的 $2\times 2$ 红色砖块完全覆盖所有蓝色区域。若可行，输出覆盖方案；否则，输出 `Impossible`。

## 解题思路

遍历整个矩形时，每个 $2\times 2$ 红色砖块的左上角会最先被访问到。因此，当遍历到 `#` 时，它应是一个红色砖块的左上角。接着检查其余三个位置是否也是 `#`。如果是，直接覆盖这四个位置；否则，无法完成覆盖。

## 参考代码

```cpp
#include <bits/stdc++.h>
using namespace std;

using ll=long long;
const int N=55;
char a[N][N];
int main()
{
	ios::sync_with_stdio(false);
	cin.tie(nullptr);
	int T;
	cin>>T;
	for(int $=1;$<=T;$++)
	{
		int r,c;
		cin>>r>>c;
		for(int i=1;i<=r;i++)
		{
			for(int j=1;j<=c;j++)
			{
				cin>>a[i][j];
			}
		}
		bool ck=1;
		for(int i=1;i<=r;i++)
		{
			for(int j=1;j<=c;j++)
			{
				if(a[i][j]!='#')continue;
				if(a[i+1][j]=='#'&&a[i][j+1]=='#'&&a[i+1][j+1]=='#')
				{
					a[i][j]=a[i+1][j+1]='/';
					a[i+1][j]=a[i][j+1]='\\';
				}
				else ck=0;
			}
		}
		cout<<"Case #"<<$<<':'<<'\n';
		if(!ck)cout<<"Impossible"<<'\n';
		else
		{
			for(int i=1;i<=r;i++)
			{
				for(int j=1;j<=c;j++)
				{
					cout<<a[i][j];
				}
				cout<<'\n';
			}
		}
	}
	return 0;
}
```

---

## 作者：YuTinMin (赞：1)

## 思路

太好了，又有题解写了。

先看题目，题目说要把蓝色瓷砖铺成红色，但红色的又只有 $2 \times 2$ 的红色瓷砖，要铺上去并且不超过边界，然后要用斜杠来表示红瓷砖。诶，那我有一计，我只看左上角的瓷砖不就行了嘛，看到一个蓝色瓷砖，下面、左边、左下边都没有超出边界，就更新到另一个字符串组里面，并换成题目要求的斜杠，原来的字符串组就把这四个遍历过的字符改成白色瓷砖，说明不需要走，没必要再弄一次了。

定义一个布尔函数 `flag`，遍历存有答案的字符串组，如果出现一个蓝色瓷砖，那就不行了，`flag` 变为假，然后输出 `Impossible`，否则就直接输出答案。

## 代码

```cpp
#include <bits/stdc++.h>
using namespace std;
string b[55], a[55]; //我用的string，也可以用char

void solve(int r, int c)
{
    for (int i = 0; i < r; ++i)
    {
        for (int j = 0; j < c; ++j)
        {
            if (a[i][j] == '#')
            {
                if (i + 1 < r && j + 1 < c && a[i][j + 1] == '#' && a[i + 1][j] == '#' && a[i + 1][j + 1] == '#')
                {
                    b[i][j] = '/';
                    b[i][j + 1] = '\\'; //加个 \ 防止斜杠冲突
                    b[i + 1][j] = '\\';
                    b[i + 1][j + 1] = '/';
                    a[i][j] = a[i][j + 1] = a[i + 1][j] = a[i + 1][j + 1] = '.'; //a数组遍历过的全部改为 .
                }
            }
        }
    }

    bool flag = true;
    for (int i = 0; i < r; ++i)
    {
        for (int j = 0; j < c; ++j)
        {
            if (a[i][j] == '#')
            {
                flag = false;
                break;
            }
        }
        if (!flag)
            break;
    }

    if (flag)
        for (int i = 0; i < r; ++i)
            cout << b[i] << endl;
    else
        cout << "Impossible" << endl;
}

int main()
{
    
    int t;
    cin >> t;
    for (int tt = 1; tt <= t; ++tt)
    {
        int r, c;
        cin >> r >> c;
        for (int i = 0; i < r; ++i)
        {
            cin >> a[i];
            b[i] = a[i]; //b数组存储答案
        }
        cout << "Case #" << tt << ":" << endl;
        solve(r, c);
    }

    system("pause"); //加不加无所谓，看习惯
    return 0;
}
```

---

## 作者：hlb44 (赞：1)

[题目传送门](https://www.luogu.com.cn/problem/P13371)

题目要求我们用红色瓷砖覆盖所有 $2 \times 2$ 的蓝色瓷砖。

那么容易发现，如果有 $2 \times 2$ 的区域内既有红色瓷砖又有蓝色瓷砖，则不合法。

我们现在先遍历每个可能的 $2 \times 2$ 区域，即从左上角开始，逐行逐列检查每个可能的 $2 \times 2$ 区域，如果区域内都是蓝色瓷砖，那么用题目的红色瓷砖来替换，同时用标记数组标记为已经使用。

代码：


```cpp
#include<bits/stdc++.h>
using namespace std;

int main() {
	int T;
	cin>>T;
	for(int case_num=1; case_num<=T; ++case_num) {
		int R,C;
		cin>>R>>C;
		vector<string> grid(R);
		for (int i=0; i<R; ++i) {
			cin>>grid[i];
		}
		vector<string> ans=grid;
		bool f=true;
		for (int i=0; i<R-1&&f; ++i) {
			for(int j=0; j<C-1&&f; ++j) {
				if(ans[i][j]=='#') {
					if(ans[i][j+1]=='#'&&ans[i+1][j]=='#'&&ans[i+1][j+1]=='#') {
						ans[i][j]='/';
						ans[i][j+1]='\\';
						ans[i+1][j]='\\';
						ans[i+1][j+1]='/';
					} else {
						f=false;
					}
				}
			}
		}
		for(int i=0; i<R&&f; ++i) {
			for(int j=0; j<C; ++j) {
				if(ans[i][j]=='#') {
					f=false;
					break;
				}
			}
		}
		cout<<"Case #"<<case_num<<":\n";
		if(f) {
			for(const string& row:ans) {
				cout<<row<<'\n';
			}
		} else cout << "Impossible\n";
	}
	return 0;
}
```

---

## 作者：Yeonjun_0913 (赞：0)

#### 题意简述
对于 $T$ 组数据，每组数据给定一个 $R$ 行 $C$ 列的矩阵，判断矩阵内的 `#` 能否被 $2 \times 2$ 的一个矩形覆盖。
#### solution
因为红色的矩形长和宽均一致，所以，我们不用考虑横着放与竖着放。只需要按题意模拟即可。遍历矩阵，每次遇到 `#`，就填充一个 $2 \times 2$ 的矩形，如果在这个矩形的范围内有白色（即 `.`），就直接输出 `Impossible`。

#### Code

```cpp
#include <iostream>
using namespace std;

int t,Case;
int r,c;
char a[55][55];
bool flag=true;
void mark(int x,int y){
    int xx=x+1,yy=y+1;
    if (a[x][y]=='#'&&a[xx][y]=='#'&&a[x][yy]=='#'&&a[xx][yy]=='#'){
        a[x][y]='/';
        a[xx][y]='\\';
        a[xx][yy]='/';
        a[x][yy]='\\';
    }else {
        flag=false;
        return;
    }
}

int main (){
    ios::sync_with_stdio(false);
    cin.tie(0);
    cout.tie(0);
    cin >> t;
    while (t--){
        flag=true;
        Case++;
        cout << "Case #" << Case << ':' << endl;
        cin >> r >> c;
        for (int i=1;i<=r;i++){
            for (int j=1;j<=c;j++){
                cin >> a[i][j];
            }
        }
        for (int i=1;i<=r;i++){
            for (int j=1;j<=c;j++){
                if (a[i][j]=='#'){
                    mark(i,j);
                    if (!flag){
                        break;
                    }
                }
            }
            if (!flag) break;
        }
        if (!flag){
            cout << "Impossible" << endl;
            continue;
        }
        for (int i=1;i<=r;i++){
            for (int j=1;j<=c;j++){
                cout << a[i][j];
            }
            cout << endl;
        }
    }
    return 0;
}
```

---

## 作者：_____1__2___ (赞：0)

# 题解：P13371 [GCJ 2011 #1C] Square Tiles

这道题给了一个 $R \times C$ 的几何图片，需要将其中的蓝色砖块转化为长宽都为二的红色砖块，那么有几种情况如下。

-   蓝色砖块总数不为四的倍数，所以一定无法完全替换
-   对于某个蓝色砖块 $a_{i,j}$，假设它位于替换砖块左上角，那么 $a_{i+1,j}$，$a_{i+1,j+1}$，$a_{i,j+1}$ 都应该是蓝色方块。
-   当满足以上条件时，更改蓝色砖块，并输出。

故代码实现如下
```cpp
#include<bits/stdc++.h>
using namespace std;

char a[100][100];

void solve() {
	int n,m,sum=0;
	cin >> n >> m;
	for (int i=1;i<=n;i++) {
		for (int j=1;j<=m;j++) {
			cin >> a[i][j];
			if (a[i][j]=='#') sum++;
		}
	}
	if (sum%4) {
		puts("Impossible");
		return ;
	}
	for (int i=1;i<=n;i++) {
		for (int j=1;j<=m;j++) {
			if (a[i][j]=='#') {
				if (i+1<=n&&j+1<=m&&a[i][j+1]=='#'&&a[i+1][j]=='#'&&a[i+1][j+1]=='#') {
					a[i][j]=a[i+1][j+1]='/';
					a[i+1][j]=a[i][j+1]='\\';
				} else {
					puts("Impossible");
					return ;		
				}
			}
		}
	}
	for (int i=1;i<=n;i++) {
		for (int j=1;j<=m;j++) {
			cout << a[i][j];
		}
		cout << '\n';
	}
	return ;
}

int main() {
	int T;
	scanf("%d", &T);
	for (int t=1;t<=T;t++) {
		printf("Case #%d:\n", t);
		solve();
	}
	return 0;
}
```
为什么使用函数 solve 因为如果直接写，就会有一串[又臭又长](https://www.luogu.com.cn/paste/koakmng2)的代码

---

