# Minesweeper

## 题目描述

One day Alex decided to remember childhood when computers were not too powerful and lots of people played only default games. Alex enjoyed playing Minesweeper that time. He imagined that he saved world from bombs planted by terrorists, but he rarely won.

Alex has grown up since then, so he easily wins the most difficult levels. This quickly bored him, and he thought: what if the computer gave him invalid fields in the childhood and Alex could not win because of it?

He needs your help to check it.

A Minesweeper field is a rectangle $ n \times m $ , where each cell is either empty, or contains a digit from $ 1 $ to $ 8 $ , or a bomb. The field is valid if for each cell:

- if there is a digit $ k $ in the cell, then exactly $ k $ neighboring cells have bombs.
- if the cell is empty, then all neighboring cells have no bombs.

Two cells are neighbors if they have a common side or a corner (i. e. a cell has at most $ 8 $ neighboring cells).

## 说明/提示

In the second example the answer is "NO" because, if the positions of the bombs are preserved, the first line of the field should be \*2\*1.

You can read more about Minesweeper in <a>Wikipedia's article</a>.

## 样例 #1

### 输入

```
3 3
111
1*1
111
```

### 输出

```
YES```

## 样例 #2

### 输入

```
2 4
*.*.
1211
```

### 输出

```
NO```

# 题解

## 作者：sounds_666 (赞：3)

这道题其实很简单，只需用考虑两种情况。

1、空的旁边有没有雷   
2、数字与雷数量是否相等    

代码有详细的注释，供大家参考
```cpp
#include<bits/stdc++.h>
using namespace std;
char mapp[1001][1001];
int n,m;
bool kkl(int x,int y){//判断合法性 
	if(x<1||y<1||x>n||y>m)return true;
	return false;
}
int main(){
	ios::sync_with_stdio(false);//加速cin,cout的速度 
	cin>>n>>m;
	for(int i=1;i<=n;i++){
		for(int j=1;j<=m;j++){
			cin>>mapp[i][j];//输入 
		}
	} 
	for(int i=1;i<=n;i++){
		for(int j=1;j<=m;j++){
			if(mapp[i][j]=='.'){//如果是空的 
				for(int p=i-1;p<=i+1;p++){//在附近3*3寻找累 
					for(int q=j-1;q<=j+1;q++){
						if(kkl(p,q))continue;
						if(mapp[p][q]=='*'){//如果是雷，就不合法
							cout<<"NO"<<endl; //直接输出
							return 0;//结束 
					 	} 
					}
				}
			}
			if(mapp[i][j]>='0'&&mapp[i][j]<='9'){//如果是数字
				int cnt=0;//记录雷的数量 
				for(int p=i-1;p<=i+1;p++){//在附近3*3寻找累 
					for(int q=j-1;q<=j+1;q++){
						if(kkl(p,q))continue;
						if(mapp[p][q]=='*'){//如果是雷
							 cnt++;//累加 
					 	} 
					}
				}
				if(cnt!=mapp[i][j]-'0'){//如果不相等 ，就不合法 
					//因为mapp是字符，所以在ASCLL码减去零
					cout<<"NO"<<endl; //直接输出
					return 0;//结束 
				}
			} 
		}
	}
	cout<<"YES"<<endl; //如果没结束那么就是合法的 
	return 0;//Nice~~
}
```

---

## 作者：МiсDZ (赞：2)

题目的大意是：

给出一个扫雷地图（大家肯定都玩过），让你求这个地图是否合法。
对于地图是否合法有两个规则：

1. 对应点的数字周围必须有对应数字个雷
2. 空的地方周围没有雷

其中"*"表示雷，"."表示这里可能是空的。

大致思路：
先对每一个雷跑一遍八个方向，建立真正的地图。
针对两项规则比较二者是否有误差。

代码如下：
```cpp
#include<bits/stdc++.h>
#define INF 0x3f3f3f
#define MAXN 1000+10 
using namespace std;
int read(){
    int x=0,f=1;
    char ch=getchar();
    while(ch>'9'||ch<'0'){if(ch=='-')f=-1;ch=getchar();}
    while(ch<='9'&&ch>='0'){x=x*10+ch-'0';ch=getchar();}
    return x*f;
}
char a[MAXN][MAXN];
int s[MAXN][MAXN];
int main(){
    int n=read(),m=read();
    for(int i=1;i<=n;i++){
        for(int j=1;j<=m;j++)
            a[i][j]=getchar();
        getchar();
    }
    for(int i=1;i<=n;i++)
        for(int j=1;j<=m;j++){
            if(a[i][j]=='*'){
                s[i+1][j]++;
                s[i-1][j]++;
                s[i][j+1]++;
                s[i][j-1]++;
                s[i+1][j+1]++;
                s[i-1][j+1]++;
                s[i+1][j-1]++;
                s[i-1][j-1]++;//记录雷
            }
        }//建立真正的地图
    for(int i=1;i<=n;i++)
        for(int j=1;j<=m;j++){
            if(a[i][j]!='*'&&a[i][j]!='.'){
                if(a[i][j]-'0'!=s[i][j]){
                    cout<<"NO\n";
                    return 0;
                }
            }
            if(a[i][j]=='.'){
                if(
                    a[i+1][j]=='*'||
                    a[i-1][j]=='*'||
                    a[i][j+1]=='*'||
                    a[i][j-1]=='*'||
                    a[i+1][j+1]=='*'||
                    a[i-1][j+1]=='*'||
                    a[i+1][j-1]=='*'||
                    a[i-1][j-1]=='*'
                    ){
                    cout<<"NO\n";
                    return 0;
                }
            }//根据规则比较两个地图
        }
        cout<<"YES\n";
        return 0;
}
```


---

## 作者：Eason_AC (赞：1)

## Content
有一个 $n\times m$ 的扫雷地图，请判断这个地图是否合法，即对于所有格子，是否满足：

- 对应点的数字周围必须有对应数字个雷
- 空的地方周围没有雷

**数据范围：$1\leqslant n,m\leqslant 100$。**
## Solution
我们需要遍历整个地图，如果有雷，就将周围所有的格子全部加 $1$，最后再判断是否和原地图完全相同即可。

注意需要考虑越界的问题。
## Code
```cpp
const int dx[8] = {0, 0, -1, 1, -1, 1, -1, 1};
const int dy[8] = {1, -1, 0, 0, 1, -1, -1, 1};
int n, m, shouldbe[107][107];
char a[107][107];

int main() {
	getint(n), getint(m);
	_for(i, 1, n) {
		scanf("%s", a[i] + 1);
		_for(j, 1, m) {
			if(a[i][j] == '*')
				_for(k, 0, 7) {
					int xx = i + dx[k], yy = j + dy[k];
					if(xx < 1 || xx > n || yy < 1 || yy > m)	continue;
					shouldbe[xx][yy]++; 
				}
		}
	}
	_for(i, 1, n)
		_for(j, 1, m)
			if((a[i][j] == '.' && shouldbe[i][j]) || (isdigit(a[i][j]) && a[i][j] - '0' != shouldbe[i][j]))	return printf("NO"), 0;
	printf("YES");
	return 0;
}
```

---

## 作者：封禁用户 (赞：0)

~~我还是太弱了~~

纯模拟，判断每一个数字周围雷的数量是否与原地图相等（空视为0）

### 注意换行

不写边界判断~~我太懒了~~，因此读入时下标起始为1

下面贴代码

```cpp
#include<iostream>
using namespace std;
char map[200][200];
int main()
{
	int n,m;
	cin>>n>>m;
	for(int i=1;i<=n;i++)
		for(int j=1;j<=m;j++)
		{
			cin>>map[i][j];
			if(map[i][j]=='.')map[i][j]='0';
		}
	for(int i=1;i<=n;i++)
		for(int j=1;j<=m;j++)
		{
			if(map[i][j]=='*')continue;
			int tmp=0;
			for(int k=-1;k<=1;k++)
				for(int t=-1;t<=1;t++)
				{
					if(k==t&&k==0)continue;
					if(map[i+k][j+t]=='*')tmp++;
				}
			if((map[i][j]-'0')!=tmp)
			{
				cout<<"NO\n";
				return 0;
			}
		}
	cout<<"YES\n";
	return 0;
}
```

其实还可以设一个数组

`
const move[][2]={{-1,-1},{-1,0},{-1,1},{0,-1},{0,1},{1,-1},{1,0},{1,1}};
`

然后原k,t的循环改为
```
for(int k=0;k<8;k++)
if(map[i+move[k][0]][j+move[k][1]]=='*')tmp++;
```

该题数据范围可以是$1<m,n<3500$

[另一道题](https://www.luogu.org/problemnew/show/CF404D
)

---

## 作者：__Hacheylight__ (赞：0)

题目大意：

给你一张地雷图，判断该地雷图是否合法。

（'.'表示空地，'*'表示雷，数字表示旁边有多少个雷）

解法：

1.读入，用scanf

2.judge

1)如果是空地，判断周围是否有雷；

2）如果是数字，判断周围的雷的数量是否跟该数字一样；

3）雷，continue ;

3.printf 

代码
```cpp
#include <bits/stdc++.h>
using namespace std ;
#define R(i,a,b) for (int i=a;i<=b;i++)
char st[110][110] ;
int dx[8]={-1,-1,-1,0,0,1,1,1} ;
int dy[8]={-1,0,1,-1,1,-1,0,1} ;
int n,m ;
bool judge(){
	R(i,1,n) R(j,1,m)
	if (st[i][j]=='.') //empty 
	R(k,0,7){ 
		int tx=i+dx[k],ty=j+dy[k] ;
		if (tx<1 || ty<1 || tx>n || ty>m) continue ;
		if (st[tx][ty]=='*') return false ;
	}
	else if (st[i][j]>='0' && st[i][j]<='9'){ //digits 
		int sum=0 ; 
		R(k,0,7){
			int tx=i+dx[k],ty=j+dy[k] ;
			if (tx<1 || ty<1 || tx>n || ty>m) continue ;
			if (st[tx][ty]=='*') sum++ ;
		} 
		int ch=st[i][j]-'0' ;
		if (ch!=sum) return false ;
	}
	return true ;
} 
int main(){
	scanf("%d %d \n",&n,&m) ;
	R(i,1,n) scanf("%s",st[i]+1) ;
	bool ans=judge() ;
	printf("%s\n",ans?"YES":"NO") ;
	return 0 ; 
}
```




---

