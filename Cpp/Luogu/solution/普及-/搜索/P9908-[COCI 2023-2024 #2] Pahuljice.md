# [COCI 2023/2024 #2] Pahuljice

## 题目描述

Lana 喜欢画雪花。如下定义一个大小为 $x$ 的雪花：

+ 雪花的中间是一个 $\texttt{'+'}$。
+ 在 $\texttt{'+'}$ 的上方和下方各有 $x$ 个 $\texttt{'|'}$。
+ 在 $\texttt{'+'}$ 的左方和右方各有 $x$ 个 $\texttt{'-'}$。
+ 在 $\texttt{'+'}$ 的左上方和右下方各有 $x$ 个 $\texttt{'\textbackslash'}$。
+ 在 $\texttt{'+'}$ 的左下方和右上方各有 $x$ 个 $\texttt{'/'}$。

雪花之间可以重叠。如下是雪花的几个例子：

![](https://cdn.luogu.com.cn/upload/image_hosting/2s81nyxm.png)

三张图分别含有一个大小为 $1$ 的雪花，重叠的两个大小分别为 $2$ 和 $1$ 的雪花，一个大小为 $1$ 的雪花（作为大小为 $2$ 的雪花不完整）。

给定一个 $n\times m$ 的字符矩阵，请找出其中最大的雪花的大小。
 

## 说明/提示

### 数据范围
|$\text{Subtask}$|分值|特殊性质|
|:-:|:-:|:-:|
|$1$|$11$|最大的雪花大小是 $1$，或者没有任何雪花|
|$2$|$11$|矩阵中至多只有一个 $\texttt{'+'}$|
|$3$|$28$|无|

对于所有数据，$1\le n,m\le 50$。

## 样例 #1

### 输入

```
5 6
\.\|/.
---+--
/./|\.
./.|.\
/..|..```

### 输出

```
1
```

## 样例 #2

### 输入

```
7 7
\.|./..
.\|/...
--+--..
./|\...
/.|.\|/
....-+-
..../|\```

### 输出

```
2```

## 样例 #3

### 输入

```
7 7
\|/|\|/
-+-|-+-
/|\|/|\
---+---
\|/|\|/
-+-|-+-
/|\|/|\
```

### 输出

```
1```

# 题解

## 作者：gaoyangyang (赞：5)

# [P9908 [COCI 2023/2024 #2] Pahuljice](https://www.luogu.com.cn/problem/P9908)


我们无论解什么题都要贯彻一个思想：**“解其题，必先知其题；何解题，必为简其题。”**
 
~~_其实就是先读题，再把问题简化成多个简单的小问题，然后一一解决，最后问题得解。_~~
 
## 首先我们来完成第一步“知其题”
### 审题又分为 $3$ 步走

1. **区分有用**的信息和**没用**的信息

从题目中我们可以简单的得出“有用的信息”。

即“**什么样**的图形是雪花”（下方是一个大小为 $x$ 的雪花的要求，同题目描述）。

- 雪花的中间是一个 ```+```。
- 在'+'的上方和下方各有 $x$ 个  ```|```。
- 在'+'的左方和右方各有 $x$ 个 ```-```。
- 在'+'的左上方和右下方各有 $x$ 个 ```/```。
- 在'+'的左下方和右上方各有 $x$ 个 ```\```。

```
//雪花大小为2：
/*
\.|./
.\|/.
--+--
./|\.
/.|.\
*/
```


以及“我们要找的目标**是什么**”——**最大雪花的大小**。


2. 将有用的信息**联系**起来

通过上面的审题我们了解到了两个关键点即“条件”和“目标”。我们要从其给出的**条件**来达成**目标**。这时我们可以列出以下大概思路：首先**找到**所有雪花，再**算出**每朵雪花的**大小**，最后**找出最大**的一朵，**输出得解**。

3. 将**有用的**信息转化为伪代码语言 

看完了题，我们要开始准备代码了。依题意可以看出在题中**怎样**是一朵雪花。我们这里用代码来表示一下：

假定雪花 $a$ 的**中心** ```+``` 的索引为 $[i][j]$。

那么其 $[i+n][j]$ 和 $[i-n][j]$ 都必须是 ```|```。

其 $[i][j+n]$ 和 $[i][j-n]$ 都必须是 ```-```。

其 $[i+n][j+n]$ 和 $[i-n][j-n]$ 都必须是 ```/```。

其 $[i-n][j+n]$ 和 $[i+n][j-n]$ 都必须是 ```\```。

如果（$0\le p\le n$）$p$ 为其间任意值都成立那么 $n$ 就是这朵雪花的大小。是不是感觉还有点模糊？没关系我们往下看。


## 接下来我们完成第二步“简其题”
刚刚我们阅读了题目，也写了“伪代码”。我们就要**化简题目**了。怎么简呢？从**判断雪花大小**的地方减。阅读规则我们不难发现每个雪花都有一个特点就是**都**有一个 ```+```，我们可以以这个 ```+``` 为**切入点**化简题目。

我们先在“图”中寻找 ```+```，如果找到了就立即开始计算其大小。怎么算呢？先前不是提到了吗？**找一个 $p$ 来帮忙**，来帮助我们**确定 $n$ 的值**也就是大小了。$p$ 作为**偏移量**一开始为 $1$ 随后**慢慢加大**直到判断为这**不再是**一朵雪花为止，而此时雪花的大小也就**确定**了，也就是 $p-1$，在比较其**是否**为**最大**的雪花就可以了。上代码：

```cpp
if (a[i][j]=='+')//判断是否为雪花中心点
	{
	int p=1;//定义偏移量p
	while(1)
	{
		if (i+p>=m or i-p<0 or j+p>=n or j-p<0)break;
		if (a[i+p][j]!='|' or a[i-p][j]!='|')break;
		if (a[i][j+p]!='-' or a[i][j-p]!='-')break;
		if (a[i+p][j+p]!=char(92) or a[i-p][j-p]!=char(92))break;
      //由于“\”有特殊意义，所以常规方法不方便书写，这里用ASCLL码表示
		if (a[i-p][j+p]!='/' or a[i+p][j-p]!='/')break;
		max_=max(p,max_);//判断这朵雪花是不是最大的
		p++;
	}
				
}
```

别走还没结束！

## 最后我们完成最后一步“解其题”
化简完了就开始解题，然后我们就会发现这是最简单的一步。

先初始化，再写输入，然后遍历图表，判断大小，比较大小，输出。这就结束了，自此，世界安静了。

然后我们遵循“Talk is cheap,show me the code.”的原则，我们上代码：

```cpp
#include<bits/stdc++.h>
using namespace std;
int main()
{
	char a[51][51];
	int m,n;
	cin>>m>>n;
	int max_=0;
	for (int i=0;i<m;i++)
	{
		for (int j=0;j<n;j++)
		{
			cin>>a[i][j];
		}
	}//初始化+输入
    
	for (int i=0;i<m;i++)
	{
		for (int j=0;j<n;j++)
		{
			if (a[i][j]=='+')//判断是否为雪花中心点
			{
				int p=1;//定义偏移量p
				while(1)
				{
					//if (p==0){p++;continue;}
              
					if (i+p>=m or i-p<0 or j+p>=n or j-p<0)break;
					if (a[i+p][j]!='|' or a[i-p][j]!='|')break;
					if (a[i][j+p]!='-' or a[i][j-p]!='-')break;
					if (a[i+p][j+p]!=char(92) or a[i-p][j-p]!=char(92))break;//由于“\”有特殊意义，所以常规方法不方便书写，这里用ASCLL码表示
					if (a[i-p][j+p]!='/' or a[i+p][j-p]!='/')break;
					max_=max(p,max_);//判断这朵雪花是不是最大的
					p++;
				}
				
			}
		}
	}
	cout<<max_;//输出
}
```

The end.

---

## 作者：Mason123456 (赞：3)

写于2023.12.24，此时的题目为【暂无评定】，综合来看，可能只有橙题难度。  
[P9908](https://www.luogu.com.cn/problem/P9908)  
题目思路：枚举每一个+，再搜索大小，大小为四个边的最小值。  
注意：因为这题范围很小，所以在 $O(n^3)$ 都没问题。  
AC代码：
```

#include <iostream>
#include <algorithm>
#include <climits>
using namespace std;
const int N = 55;//好习惯，推荐以后数组范围都用const
int c,r;//长&宽，c为行数
char a[N][N];
int ans = 0;
int main() {
    cin>>c>>r;
    for(int i = 1;i <= c;i++){
        for(int j = 1;j <= r;j++){
            cin>>a[i][j];
        }
    }
    for(int i = 1;i <= c;i++){
        for(int j = 1;j <= r;j++){
            if(a[i][j] == '+'){
                int len = INT_MAX;
                //从这里开始，枚举八个方向
                int k;
                int l = 0;
                for(k = i - 1;k >= 1;k--){//上
                    if(a[k][j] != '|'){
                        break;
                    }
                    l++;
                }
                len = min(l,len);
                l = 0;
                for(k = i + 1;k <= c;k++){//下
                    if(a[k][j] != '|'){
                        break;
                    }
                    l++;
                }
                len = min(l,len);
                l = 0;
                for(k = j - 1;k >= 1;k--){//左
                    if(a[i][k] != '-'){
                        break;
                    }
                    l++;
                }
                len = min(l,len);
                l = 0;
                for(k = j + 1;k <= r;k++){//右
                    if(a[i][k] != '-'){
                        break;
                    }
                    l++;
                }
                len = min(l,len);
                l = 0;
                int x,y;//两个方向
                for(x = i-1,y = j-1; x>=1 && y>=1; x--,y--){//左上
                    if(a[x][y] != '\\'){//注意\为空字符，所以不能用\，要用\\
                        break;
                    }
                    l++;
                }
                len = min(l,len);
                l = 0;
                for(x = i-1,y = j+1; x>=1 && y<=r; x--,y++){//右上
                    if(a[x][y] != '/'){
                        break;
                    }
                    l++;
                }
                len = min(l,len);
                l = 0;
                for(x = i+1,y = j-1; x<=c && y>=1; x++,y--){//左下
                    if(a[x][y] != '/'){
                        break;
                    }
                    l++;
                }
                len = min(l,len);
                l = 0;
                for(x = i+1,y = j+1; x<=c && y<=r; x++,y++){//右下
                    if(a[x][y] != '\\'){
                        break;
                    }
                    l++;
                }
                len = min(l,len);
                ans = max(ans,len);
            }
        }
    }
    if(ans != INT_MAX)cout<<ans;
    else cout<<0;
    return 0;
}


```



---

## 作者：allqpsi (赞：2)

### 个人评估：橙题而已。

题意简述：给你一个图，让你求最大的雪花有多大（雪花是什么见题目）。

做法：这还用问吗？一看数据范围，直接上暴力。在图中找每一个开端，暴力找这个雪花有多大，取最大就行了。

#### 费话不多说，代码来了：

```cpp
#include<bits/stdc++.h>
#define int long long
using namespace std;
int n,m,a=0,ans=0;
char vi[55][55];
signed main(){
	cin>>n>>m;
	for(int i=1;i<=n;i++){
		for(int j=1;j<=m;j++){
			cin>>vi[i][j];
		}
	}
	for(int i=1;i<=n;i++){
		for(int j=1;j<=m;j++){
			if(vi[i][j]!='+'){
				continue;
			}
			for(int k=1;k<=n;k++){
				if(i-k<1||vi[i-k][j]!='|'){
					a=k-1;
					break;
				}
				if(i+k>n||vi[i+k][j]!='|'){
					a=k-1;
					break;
				}
			}
			for(int k=1;k<=n;k++){
				if(i-k<1||vi[i-k][j-k]!='\\'){
					a=min(a,k-1);
					break;
				}
				if(i+k>n||j+k>m||vi[i+k][j+k]!='\\'){
					a=min(a,k-1);
					break;
				}
			}
			for(int k=1;k<=n;k++){
				if(j-k<1||vi[i][j-k]!='-'){
					a=min(a,k-1);
					break;
				}
				if(j+k>m||vi[i][j+k]!='-'){
					a=min(a,k-1);
					break;
				}
			}
			for(int k=1;k<=n;k++){
				if(i-k<1||j+k>m||vi[i-k][j+k]!='/'){
					a=min(a,k-1);
					break;
				}
				if(i+k>n||j-k<1||vi[i+k][j-k]!='/'){
					a=min(a,k-1);
					break;
				}
			}
			ans=max(ans,a);
		}
	}
	cout<<ans;
}
```


---

## 作者：pm_fp (赞：1)

第一眼数据范围，我释怀的笑。

直接找到雪花中心，然后沿四边查找上，下，左，右，左上，左下，右上，右下的长度就好，雪花的大小就是这八个长度的最小值。

```
#include<bits/stdc++.h>
using namespace std;
char nm[55][55];
int main(){
	int n,m;
	int ans;
	int s=0,x=0,z=0,y=0,zs=0,ys=0,zx=0,yx=0;
	cin>>n>>m;
	for(int i=1;i<=n;i++){
		for(int j=1;j<=m;j++){
			cin>>nm[i][j];
		}
	}
	int dx=0,c=0;
	for(int i=1;i<=n;i++){
		for(int j=1;j<=m;j++){
			if(nm[i][j]=='+'){//找到雪花中心 
				s=0,x=0,z=0,y=0,zs=0,ys=0,zx=0,yx=0;
				for(int l=1;;l++){//开始向四周搜索，越界或不符合雪花形状就跳出 
					if(i-l>0&&nm[i-l][j]=='|') s++;//上 
					else{
						c=s;
						break;
					}
					if(i-l>0&&nm[i+l][j]=='|') x++;//下 
					else{
						c=x;
						break;
					}
					if(j-l>0&&nm[i][j-l]=='-') z++;//左 
					else{
						c=z;
						break;
					}
					if(j-l>0&&nm[i][j+l]=='-') y++;//右 
					else{
						c=y;
						break;
					}
					if(i-l>0&&j-l>0&&nm[i-l][j-l]=='\\') zs++;//左上 
					else{
						c=zs;
						break;
					}
					if(i-l>0&&j-l>0&&nm[i-l][j+l]=='/') ys++;//右上 
					else{
						c=ys;
						break;
					}
					if(i-l>0&&j-l>0&&nm[i+l][j-l]=='/') zx++;//左下 
					else{
						c=zx;
						break;
					}
					if(i-l>0&&j-l>0&&nm[i+l][j+l]=='\\') yx++;//右下 
					else{
						c=yx;
						break;
					}
				}
				dx=max(dx,c);//考虑两种及以上片雪花，取最大值 
			}
		}
	}
	cout<<dx;
	return 0;
}
```

---

## 作者：cff_0102 (赞：1)

数据范围很小，考虑直接暴力枚举每个雪花中心，计算这个雪花的大小，然后更新答案。

怎么计算雪花的大小？从中心开始逐渐向外扩展，如果碰到边缘或者哪一圈的字符不符合雪花定义，就退出循环。

下面的代码为了看着清晰，有些内容被判断了多次，如 `i-s>=0` 就被判断了 $3$ 次，不过没什么影响，编译器也会把它优化掉。

需要注意的是，因为 `\` 是转义字符，所以要用 `'\\'` 表示字符 `\`。

```cpp
#include<bits/stdc++.h>
using namespace std;
char c[50][50]; 
int main(){
	ios::sync_with_stdio(false);
	int n,m;cin>>n>>m;
	for(int i=0;i<n;i++){
		cin>>c[i];
	}//输入
	int mx=0;
	for(int i=0;i<n;i++){
		for(int j=0;j<m;j++){
			if(c[i][j]=='+'){//如果是中心
				int x=0;
				for(int s=1;;s++){//向外扩展
					if(i-s>=0&&j-s>=0&&c[i-s][j-s]=='\\'//左上
					 &&i-s>=0&&        c[i-s][j]=='|'   //上
					 &&i-s>=0&&j+s<m &&c[i-s][j+s]=='/' //右上
					 &&        j-s>=0&&c[i][j-s]=='-'   //左
					 &&        j+s<m &&c[i][j+s]=='-'   //右
					 &&i+s<n &&j-s>=0&&c[i+s][j-s]=='/' //左下
					 &&i+s<n &&        c[i+s][j]=='|'   //下
					 &&i+s<n &&j+s<m &&c[i+s][j+s]=='\\'//右下
					){
						x++;
					}else{
						break;
					}
				}
				mx=max(mx,x);
			}
		}
	}
	cout<<mx;
	return 0;
}
```

---

## 作者：xuan_gong_dong (赞：1)

## 题面
[P9908 [COCI 2023/2024 #2] Pahuljice](https://www.luogu.com.cn/problem/P9908)
## 分析
看到数据范围 $1 \le n,m \le 50$，可以直接暴力解决，暴力枚举每一个节点是否为雪花的中心，如果是，暴力向八个方向拓展直到不合法，该节点为中心的雪花大小就是八个方向拓展长度的最小值。

然后就没了，时间复杂度是 $n^3$，随便过。
## Code
```cpp
#include<bits/stdc++.h>
using namespace std;
int nxt[8][2]={{0,1},{1,0},{0,-1},{-1,0},{1,1},{1,-1},{-1,1},{-1,-1}};
char check[8]={'-','|','-','|',92,'/','/',92};
char c[100][100];
int n,m;
int Max;
int main()
{
	scanf("%d%d",&n,&m);
	for(int i=1;i<=n;i++)
	{
		scanf("%s",c[i]+1);
	}
	for(int i=1;i<=n;i++)
	{
		for(int j=1;j<=m;j++)
		{
			if(c[i][j]=='+')
			{
				int Min=0x7f7f7f7f;
				for(int k=0;k<8;k++)
				{
					int tx=i,ty=j;
					int tmp=1;
					while(c[tx+tmp*nxt[k][0]][ty+tmp*nxt[k][1]]==check[k])tmp++;
					Min=min(Min,tmp-1);
				}
//				cout<<i<<' '<<j<<' '<<Min<<endl;
				Max=max(Max,Min);
			}
		}
	}
	printf("%d",Max);
	return 0;
}
```


---

## 作者：shortintlonglong (赞：0)

题目思路：  
因为数据范围仅为 $1\le n,m\le 50$，所以暴力就可以过了。  
~~你绝对想不到暴力我写了2h~~   
时间复杂度：  
$O(n^3)$。  
优化（贪心）：
如果以这个字符为中心块，如果无法"成为"一个大小为 $x$ 的雪花，那么也无法成为大小大于 $x$ 的雪花。  
代码（核心思路）：
```cpp
for (int i = 1; i <= n; i ++) {
        for (int j = 1; j <= m; j ++) {
            if (a[i][j] != '+') continue;
            int max_x = min(min(i, n - i + 1), min(j, m - j + 1)) - 1;
            int y = -1e9;
            for (int x = 1; x <= max_x; x ++) {
                bool flag = true;
                for (int I = i - x; I <= i - 1; I ++) {
                    if (a[I][j] != '|') {
                        flag = false;
                        break;
                    }
                }
                if (!flag) break;
                for (int I = i + 1; I <= i + x; I ++) {
                    if (a[I][j] != '|') {
                        flag = false;
                        break;
                    }
                }
                if (!flag) break;
                for (int J = j - x; J <= j - 1; J ++) {
                    if (a[i][J] != '-') {
                        flag = false;
                        break;
                    }
                }
                if (!flag) break;
                for (int J = j + 1; J <= j + x; J ++) {
                    if (a[i][J] != '-') {
                        flag = false;
                        break;
                    }
                }
                if (!flag) break;
                for (int I = i - x, J = j - x; I <= i + x && J <= j + x; I ++, J ++) {
                    if ((a[I][J] == '\\') || (i == I && j == J)) {
                    	
					} else {
                        flag = false;
                        break;
                    }
                }
                if (!flag) break;
                for (int I = i - x, J = j + x; I <= i + x && J >= j - x; I ++, J --) {
                    if ((a[I][J] == '/') || (i == I && j == J)) {
                    	
					} else {
                        flag = false;
                        break;
                    }
                }
                if (!flag) break;
				else y = max(x, y);
            }
            res = max(res, y);
        }
    }
```
-----
[提交记录](https://www.luogu.com.cn/record/140786867)

---

## 作者：luogu10086 (赞：0)

[传送门](https://www.luogu.com.cn/problem/P9908)

### PART 1

题目大意：

给定一坨字符雪花图，找出最大的雪花。

一个雪花的大小如何定义？

一个大小为 $x$ 的雪花就是以 `+` 为中心，上下都有 $x$ 个 `|`，左右都有 $x$ 个 `-`，左上到右下一共 $x$ 个 `\`，右上到左下 $x$ 个 `/`。

比如大小为 $3$ 的雪花就是：

```
\..|../
.\.|./.
..\|/..
---+---
../|\..
./.|.\.
/..|..\
```

------------

### PART 2

整体思路：

应该是用搜索，~~但是懒得写~~，所以决定使用最淳朴的解法——暴力。

就是先找到一个 `+`，从上下左右，左上左下，右上右下八个方向遍历。由于雪花会重叠，所以我们得求长度的**最小值**，得出一个雪花的大小，再求所有雪花的大小的**最大值**即可。




------------

### PART 3

代码实现：

```cpp
#include<bits/stdc++.h>
using namespace std;
int n,m,ans=1919810,nans=-1919810,flag=0;
/*
flag 存雪花个数
nans 是最终答案
ans 是每个雪花大小
*/
char mp[600][600]={0};
int main(){
    cin>>n>>m;
    for(int i = 1;i <= n;i++)//懒得判边界
    for(int j = 1;j <= m;j++)//所以是从 1 枚举到 n 和 m
    cin >> mp[i][j];

    for(int i = 1;i <= n;i++){
        for(int j = 1;j <= m;j++){
            if(mp[i][j]=='+'){
                flag++;
                int x=i,y=j;//记录位置，方便归位
                int cnt=0;//记长度
                ans=1919810;
                
                while(mp[++i][j]=='|')cnt++;
                ans=min(ans,cnt);//向下

                cnt=0;
                i=x;
                while(mp[--i][j]=='|')cnt++;
                ans=min(ans,cnt);//向上

                cnt=0;
                i=x;
                while(mp[i][++j]=='-')cnt++;
                ans=min(ans,cnt);//右

                cnt=0;
                j=y;
                while(mp[i][--j]=='-')cnt++;
                ans=min(ans,cnt);//左

                cnt=0;
                j=y;
                while(mp[++i][++j]=='\\')cnt++;
                ans=min(ans,cnt);//右下

                cnt=0;
                j=y,i=x;
                while(mp[--i][--j]=='\\')cnt++;
                ans=min(ans,cnt);//左上

                cnt=0;
                j=y,i=x;
                while(mp[++i][--j]=='/')cnt++;
                ans=min(ans,cnt);//左下

                cnt=0;
                j=y,i=x;
                while(mp[--i][++j]=='/')cnt++;
                ans=min(ans,cnt);//右上

                j=y,i=x;
                cnt=0;
                nans=max(nans,ans);//存更大的雪花的大小
            }
        }
    }

    if(flag>0)cout<<nans;//判断有没有雪花
    else cout<<0;//没雪花就输出 0
}
```

---

## 作者：fish_shit (赞：0)

此题按照题意模拟即可。

先寻找加号，然后再循环判断找到的这个雪花的大小，最后统计一下取个最大值，这题就解决完了。

代码
```cpp
#include<bits/stdc++.h>
using namespace std;
char a[100][100];
int maxn,n,m,k,ans,cnt;
int main(){
	cin>>n>>m;
	for(int i=1;i<=n;i++){
		for(int j=1;j<=m;j++){
			cin>>a[i][j];
		}
	} 
	for(int i=1;i<=n;i++){
		for(int j=1;j<=m;j++){
			if(a[i][j]=='+'){//找到加号
				ans=0;
				for(k=1;k<=min(min(i-1,n-i),min(j-1,m-j));k++){//判断雪花大小 
					cnt=0;
					if(a[i-k][j]=='|')cnt++;
					if(a[i+k][j]=='|')cnt++;
					if(a[i][j+k]=='-')cnt++;
					if(a[i][j-k]=='-')cnt++;
					if(a[i+k][j+k]==char(92))cnt++;
					if(a[i-k][j-k]==char(92))cnt++;
					if(a[i+k][j-k]=='/')cnt++;
					if(a[i-k][j+k]=='/')cnt++;
					if(cnt!=8){
						break;
					}
					ans++;
				}
				if(maxn<ans){//取最大值 
					maxn=ans;
				}
			}
		}
	}
	cout<<maxn;
	return 0;
}

```


---

## 作者：Cute__yhb (赞：0)

## 思路
数据很小，直接枚举。

先枚举每个可以成为中心的地方，从这里向外延伸，再依次判断。

如果当前是第 $k$ 层，中心点为 $(x,y)$，对应点则为 $(x+k\times dx_{i},y+k\times dy_{i})$。
## 代码
```cpp
#include<bits/stdc++.h>
using namespace std;
int n,m;
char a[55][55];
//方向数组
int dx[]={0,-1,1,0,0,-1,1,-1,1};
int dy[]={0,0,0,1,-1,-1,1,1,-1};
//          |   -     \   / 
int main(){
	cin>>n>>m;
	for(int i=1;i<=n;i++){
		for(int j=1;j<=m;j++){
			cin>>a[i][j];
		}
	}
	int ans=0;
	for(int i=1;i<=n;i++){
		for(int j=1;j<=m;j++){
			if(a[i][j]!='+') continue;
			int k;
			for(k=1;k<=n;k++){
				bool f=1;
				//上下
				for(int l=1;l<=2;l++){
					int xx=i+k*dx[l],yy=j+k*dy[l];
					if(xx<1||xx>n||yy<1||yy>m||a[xx][yy]!='|'){
						f=0;
						break;
					}
				}
				//左右
				for(int l=3;l<=4;l++){
					int xx=i+k*dx[l],yy=j+k*dy[l];
					if(xx<1||xx>n||yy<1||yy>m||a[xx][yy]!='-'){
						f=0;
						break;
					}
				}
				//左上方和右下方
				for(int l=5;l<=6;l++){
					int xx=i+k*dx[l],yy=j+k*dy[l];
					if(xx<1||xx>n||yy<1||yy>m||a[xx][yy]!='\\'){
						f=0;
						break;
					}
				}
				//左下方和右上方
				for(int l=7;l<=8;l++){
					int xx=i+k*dx[l],yy=j+k*dy[l];
					if(xx<1||xx>n||yy<1||yy>m||a[xx][yy]!='/'){
						f=0;
						break;
					}
				}
				if(!f) break;//不可行
				ans=max(ans,k);//更新答案
			}
		}
	}
	cout<<ans;
    return 0;
}
```


---

## 作者：xiangyanhao (赞：0)

为了对雪花进行判断，我们需要找到给出的字符矩阵中的 `+` 字符，然后从这一位置开始向外扩展即可。扩展的方法如下：

对于每一个 `+` 字符的所在位置 $(i,j)$，用 $x$ 变量表示当前雪花的大小。这样，雪花最外面的需要判断的位置就是 $(i\pm x,j)$（上下）、$(i,j\pm x)$（左右）、$(i\pm x,j\pm x)$（左上和右下）、$(i\pm x,j\mp x)$（左下和右上）。如果这些位置均未越界且都符合题目中所给的条件，则证明当前可以构成雪花，进行 $x\gets x+1$ 操作后继续循环；否则证明当前构不成雪花，雪花的大小比当前的 $x$ 小 $1$，因此跳出循环，进行 $x\gets x-1$ 操作，然后用 $x$ 更新答案。

```cpp
#include<bits/stdc++.h>
using namespace std;
int n,m;
bool pos_valid(int x,int y){ //判断坐标是否合法
	return 1<=x&&x<=n&&1<=y&&y<=m;	
}
char sn[55][55];
int main(){
	cin >> n >> m;
	for(int i = 1;i <= n;i++){
		for(int j = 1;j <= m;j++){
			cin >> sn[i][j];
		}
	}
	int ans = 0;
	for(int i = 1;i <= n;i++){
		for(int j = 1;j <= m;j++){
			if(sn[i][j]=='+'){
				int x = 1;
				while(pos_valid(i-x,j-x)&&pos_valid(i-x,j+x)&&pos_valid(i+x,j-x)&&pos_valid(i+x,j+x)&&
				(sn[i][j-x]=='-'&&sn[i][j+x]=='-'&&sn[i-x][j]=='|'&&sn[i+x][j]=='|'&&sn[i-x][j-x]=='\\'&&sn[i+x][j+x]=='\\'&&sn[i+x][j-x]=='/'&&sn[i-x][j+x]=='/')){
					x++;
				}
				x--; //最后一次x++之后是不能构成雪花的，因此要减去
				ans = max(ans,x);
			}
		}
	}
	cout << ans;
}
```

---

## 作者：zxh923 (赞：0)

# P9908 [COCI 2023/2024 #2] Pahuljice 题解

[题目传送门](https://www.luogu.com.cn/problem/P9908)

### 分析

观察数据发现 $n$ 和 $m$ 非常小，于是考虑搜索。

当我们遇到一个点是中心，向八个方向搜索即可。

这里注意判断 `\` 要写成 `\\`。

### 代码

```cpp
#include<bits/stdc++.h>
#define int long long//防止忘开long long，虽然这道题用不上 
#define N 55
using namespace std;
int n,m,ans;
char a[N][N];
signed main(){
	cin>>n>>m;
	for(int i=1;i<=n;i++){
		for(int j=1;j<=m;j++){
			cin>>a[i][j];
		}
	}
	for(int i=1;i<=n;i++){
		for(int j=1;j<=m;j++){
			if(a[i][j]=='+'){//如果是中心 
				for(int k=1;;k++){
					if(i-k>0&&j-k>0&&i+k<=n&&j+k<=m){//判断越界 
						if(a[i-k][j-k]=='\\'&&a[i-k][j]=='|'&&a[i-k][j+k]=='/'&&a[i][j+k]=='-'&&a[i+k][j+k]=='\\'&&a[i+k][j]=='|'&&a[i+k][j-k]=='/'&&a[i][j-k]=='-')ans=max(ans,k);//找最大的答案 
						else{
							break;//否则不满足直接跳出循环 
						}
					}
					else{
						break;//否则不满足直接跳出循环 
					}
				}
			}
		}
	}
	cout<<ans;
	return 0;
}

```


---

## 作者：Gaoyx (赞：0)

看了一下题，又看了范围，明显暴力能过。
## 思路
以雪花的中心加号，开始向八个方向遍历，每够了八个就是一层，雪花大小就加一，建议结合代码理解。

## 代码
```
#include<bits/stdc++.h>
using namespace std;
int n, m, tot, ans, ma = -1, qwq=1;
char a[51][51];
int dx[8] = {1,1,1,0,0,-1,-1,-1};
int dy[8] = {0,-1,1,1,-1,1,0,-1};
char b[9];
int main()
{
	b[1] = '|',b[2] = '/',b[3] = '\\',b[4] = '-';
	b[5] = '-',b[6] = '/',b[7] = '|',b[8] = '\\';
	cin >> n >> m;
	for(int i=1;i<=n;i++)
	{
		for(int j=1;j<=m;j++)
		{
			cin >> a[i][j];
		}
	}
	for(int i=1;i<=n;i++)
	{
		for(int j=1;j<=m;j++)
		{
			if(a[i][j] == '+')
			{
				while(a[i+qwq*dx[tot]][j+qwq*dy[tot]] == b[tot+1])
				{
					tot++;
					if(tot == 8)
					{
						tot = 0;
						qwq++;
					}
				}
				ma = max(ma,qwq-1);
				tot = 0;
				qwq = 1;
			}
		}
	}
	cout << ma;
	return 0;
}
```



---

## 作者：jqQt0220 (赞：0)

题目把雪花的定义写的很清楚了。养成看数据范围的好习惯，读完题直接看数据范围，发现 $1\le n,m\le 50$。那这就好写了啊，直接上暴力代码：
```cpp
/*
皇帝的新缺省源
*/
const int _mxn=50+5;
int n,m;
char a[_mxn][_mxn];
bool check(int s,int x,int y)//判断是否存在以 (x,y) 为中心的大小为 s 的雪花
{
    for(int k=1;k<=s;k++)
        if(a[x-k][y]!='|'||a[x+k][y]!='|'||//上下 s 格是否都为 '|'
        a[x][y-k]!='-'||a[x][y+k]!='-'||//左右 s 格是否都为 '-'
        a[x-k][y-k]!='\\'||a[x+k][y+k]!='\\'||//左上右下 s 格是否都为 '\'（因为反斜杠需要转义，所以要输入 '\\'）
        a[x-k][y+k]!='/'||a[x+k][y-k]!='/')//左下右上 s 格是否都为 '/'
            return false;//一个不是就整个不是
    return true;//都是了
}
int main()
{
    ___();
    cin>>n>>m;
    for(int i=1;i<=n;i++)
        for(int j=1;j<=m;j++)
            cin>>a[i][j];
    int as=0;
    for(int i=2;i<n;i++)//边上不可能有，所以 2~n-1
    {
        for(int j=2;j<m;j++)//同上
        {
            if(a[i][j]=='+')//找到雪花中心
            {
                do//这里是直接把答案往上加，因为如果算出来的答案比之前的答案小也没意义，所以直接往上加
                {
                    as++;
                }while(check(as,i,j));//没这么大的了
                as--;//多加了一个，减回去
            }
        }
    }
    cout<<as<<endl;
    return 0;//完美结束 QwQ
}
```

---

