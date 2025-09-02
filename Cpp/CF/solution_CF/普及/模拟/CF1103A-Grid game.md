# Grid game

## 题目描述

You are given a 4x4 grid. You play a game — there is a sequence of tiles, each of them is either 2x1 or 1x2. Your task is to consequently place all tiles from the given sequence in the grid. When tile is placed, each cell which is located in fully occupied row or column is deleted (cells are deleted at the same time independently). You can place tile in the grid at any position, the only condition is that tiles (and tile parts) should not overlap. Your goal is to proceed all given figures and avoid crossing at any time.

## 说明/提示

Following image illustrates the example after placing all three tiles:

 ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF1103A/f44ced4ce1b8e75991a91740b20934be3a232e59.png) Then the first row is deleted:  ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF1103A/e3af979e6215ad9ab1b846acdc74747882bc4def.png)

## 样例 #1

### 输入

```
010
```

### 输出

```
1 1
1 2
1 4```

# 题解

## 作者：miaokehao (赞：6)

一道构造题
显然可以把竖直的都放在第一行，水平的都放在最后一行
```
#include<bits/stdc++.h>
#define res register int
using namespace std;
string s;
int main(){
    cin>>s;
    res x=0,y=0;
    for(res i=0;i<s.size();i++)
        if(s[i]=='0')printf("1 %d\n",x+1),x=(x+1)%4;
        else printf("4 %d\n",y+1),y=(y+2)%4;
    return 0;
}
```

---

## 作者：世末OIer (赞：3)

看着前面的题解，感觉自己实在是太弱了。。。

模拟构造：

横着的从上往下再从左往右找，竖着的从左往右再从上往下找

下文就不解释了（模拟）

```cpp
#include<bits/stdc++.h>
using namespace std;
int n;
string s;
char c[4][4];
int main(){
	ios_base::sync_with_stdio(false);
	cin.tie(0);
	cout.tie(0);
	cin>>s;
	n=s.size();
	int i,j,f;
	for(i=0;i<4;++i) for(j=0;j<4;++j) c[i][j]='.';
	for(f=0;f<n;++f){
		if(s[f]=='0'){
			bool ok=1;
			for(j=0;j<4,ok;++j) for(i=0;i<3;++i) if(c[i][j]=='.' and c[i+1][j]=='.'){
				cout<<i+1<<' '<<j+1<<endl;
				c[i][j]='#';
				c[i+1][j]='#';
				ok=0;
				break;
			}
		}else{
			bool t=0;
			for(i=0;i<4;++i){
				for(j=0;j<3;++j){
					if(c[i][j]=='.' and c[i][j+1]=='.'){
						cout<<i+1<<' '<<j+1<<endl;
						c[i][j]='#';
						c[i][j+1]='#';
						t=1;
						break;
					}
				}
				if(t) break;
			}
		}
		for(i=0;i<4;++i){
			bool ok=1;
			for(j=0;j<4;++j) if(c[i][j]=='.') ok=0;
			if(ok) for(j=0;j<4;++j) c[i][j]='.';
		}
		for(j=0;j<4;++j){
			bool ok=1;
			for(i=0;i<4;++i) if(c[i][j]=='.') ok=0;
			if(ok) for(i=0;i<4;++i) c[i][j]='.';
		}
/*		cerr<<s[f]<<"\n";
		for(i=0;i<4;++i){
			for(j=0;j<4;++j) cout<<c[i][j]<<' ';
			cout<<endl;
		}
		cout<<endl;
*/	}
	return 0;
}
```

---

## 作者：_zqh_ (赞：1)

# 思路简述

本题较为简单，一道构造题。

构造的主旨是尽量把所有的方块都消掉，这样就能尽量避免重叠。

我们随意放一个竖着的方块：

![](https://cdn.luogu.com.cn/upload/image_hosting/j2ex85ya.png)

此时如果再来一个竖着的方块，即可放在 $\texttt{(3,1)}$ 的位置消除。

若此时来一个横着的方块，则大概是这样：

![](https://cdn.luogu.com.cn/upload/image_hosting/we5w1kq6.png)

所以，构造方法就是来一个竖着的就放在最左一列，横着的放在最后一行。

# Code

```cpp
#include <bits/stdc++.h>
#define ios                  \
ios::sync_with_stdio(0); \
cin.tie(0);              \
cout.tie(0)
// #pragma GCC optimize(2)
#define ll long long
#define pll pair<ll, ll>
#define pii pair<int, int>
#define il inline
#define p_q priority_queue
#define u_m unordered_map
#define r_g register
#define NR Nothing::read
#define NW Nothing::write
using namespace std;

string s;
bool Take0 = false, Take1 = false;

signed main() {
	ios;
	cin >> s;
	for (int i = 0; i < s.size(); i++) {
		if (s[i] == '0') {
			if (!Take0) {
				cout << "1 1\n";
			} else {
				cout << "3 1\n";
			}
			Take0 ^= 1;
		}
		if (s[i] == '1') {
			if (!Take1) {
				cout << "4 3\n";
			} else {
				cout << "4 1\n";
			}
			Take1 ^= 1;
		}
	}
	return 0;
}

```

---

## 作者：Stars_visitor_tyw (赞：1)

## CF1103A Grid game 题解
### 分析
构造题。

结论：将竖着的放第一行，横着的放第四行即可。

横着的在第四行每次放满两块小木条就会消除掉，第四行就空出来了，相当于又可以从第四行第一列开始放，且只会在第四行放，不会出现放满的情况。竖着的占据了第一行和第二行，当第一行和第二行放满四块小木条后就自动清空了，就又可以从第一行第一列开始摆放，且只会占据第一行和第二行，也不会出现放满等情况。

### 代码
```cpp
#include<bits/stdc++.h>
#define int long long
using namespace std;
const int mod=4;
string s;
int x=0, y=0;
signed main()
{
    cin>>s;
    for(int i=0;i<s.size();i++)
    {
        if(s[i]=='0')
        {
            cout<<"1 "<<x+1<<"\n";//由于模数是4，则取模结果在0~3之间，但列数是从1开始的，所以要将结果增加1
            x=(x+1)%mod;
        }
        else
        {
            cout<<"4 "<<y+1<<"\n";
            y=(y+2)%mod;//横着摆放占据2格
        }
    }
    return 0;
}
```

---

## 作者：Hooch (赞：1)

我们读了题之后发现每次放都有一个显然的规律。

样例能如下放：

![](https://cdn.luogu.com.cn/upload/image_hosting/hetjhxs0.png)

变成：

![](https://cdn.luogu.com.cn/upload/image_hosting/yh8j5j0z.png)

再成：

![](https://cdn.luogu.com.cn/upload/image_hosting/qoy33ih8.png)

只要把竖着的放在第一列和第二列，把横着的放在最后一列，就**永远不会重合**。

如果放满了就放在第一个。

证明：

首先竖着的不可能和横着的形成完整的一竖列。

接着每次放完了就可以消除，所以能放在第一个。

代码：（注：这个代码是按照横着的放在第一行，竖着的放在第 $n - 1$ 行）

```cpp
#include <bits/stdc++.h>
using namespace std;
const int N = 1e5 + 5;
char s[10005]; int cnt1, cnt2;
signed main(void) { 
	ios::sync_with_stdio(0);
	cin >> s + 1; cnt1 = cnt2 = 1;
    //cnt1 表示横着的下次放在哪
    //cnt2 表示竖着的下次放在哪
	for (int i(1); i <= strlen(s + 1); ++i) {
		if (s[i] == '1') {
			printf("%d %d\n", 1, cnt1);
			if (cnt1 == 3) cnt1 = 1;
			else cnt1 = 3;
		} else {
			printf("%d %d\n", 3, cnt2);
			if (cnt2 == 4) cnt2 = 1;
			else ++cnt2;
		}
	}
}
```



---

## 作者：__hjwucj__ (赞：0)

# 题解：CF1103A Grid game

## 思路

这是一道构造题，可以使用贪心。

很容易想到，可以把横的填在最后一行，把竖的填在最后一列，就解决了。

~~证明略。。。~~

## 代码

```cpp
#include <bits/stdc++.h>
#define int long long
#define pr printf
using namespace std;
string s;
int x,y;
signed main ()
{
	cin>>s;
	for (int i=0;i<s.size ();i++)
		if (s[i]=='0') cout<<"1 "<<x+1<<endl,x+=1,x%=4;
			else cout<<"4 "<<y+1<<endl,y+=2,y%=4;
	return 0;
}

```

---

## 作者：fmdd_szx (赞：0)

[原题](https://www.luogu.com.cn/problem/CF1103A)

# 思路

将竖着的都放在前两行，横着的放在最后一行。

维护坐标，模拟即可。

# Code
```cpp
#include<bits/stdc++.h>
using namespace std;
int l,i,x,y;
char s[1001];
signed main(){
    ios::sync_with_stdio(0);
    cin.tie(0);cout.tie(0);
    cin>>s+1;
    l=strlen(s+1);
    for(i=1;i<=l;i++)
        if(s[i]=='0') cout<<"1 "<<x+1<<"\n",x=(x+1)%4;
        else cout<<"4 "<<y+1<<"\n",y=(y+2)%4;
    return 0;
}
```


---

## 作者：FiraCode (赞：0)

## 思路：
显然可以考虑第一行放横着的，第二行放竖着的，然后用变量维护一下各自的 $y$ 坐标，看是否充满一行即可。

## Code：
```cpp
#include <bits/stdc++.h>

using namespace std;

string s;
int Y0 = 1, Y1 = 1;

int main() {
	cin >> s;

	for (int i = 0; i < (int)s.size(); ++i) {
		if (s[i] == '0') {
			printf("2 %d\n", Y1);

			Y1++;
			if (Y1 > 4) Y1 = 1;
		} else {
			printf("1 %d\n", Y0);

			Y0 += 2;
			if (Y0 > 4) Y0 = 1;
		}
	}

	return 0;
}
```

---

## 作者：Six_chestnuts (赞：0)

# 思路

简单的思想题。

将竖着放的放在第一行，放满了的时候就会全部消掉，而横着放的则就放到第三行或者第四行即可，一旦放满了就会消掉。其他的按照题意模拟即可。

## 代码

```
#include<bits/stdc++.h>
#define int long long
using namespace std;
string s;
int x,y;
signed main()
{
    cin>>s;
    for(int i=0;i<s.size();i++)
    {
        if(s[i]=='1')
        {
            y%=2;
            cout<<3<<" "<<y*2+1<<"\n";//本人写的是横着的放在第三行的写法。
            y++;
        }
        else
        {
            x%=4;
            cout<<1<<" "<<x+1<<"\n";
            x++;
        }
    }
    return 0;
}
```


---

## 作者：Bc2_ChickenDreamer (赞：0)

# CF1103A Grid game 题解

## Sol

结论：把竖直的都放在第一行，横着的都放在第 $4$ 行（最后一行），就**永远不会重合**。

证明：首先竖直的**永远不可能**和横着的组成完整的一列。每次放完了就可以消除，所以**能**放在第一个。

## Code

```cpp
#include <iostream>
#include <algorithm>
#include <cmath>
#include <cstring>
#include <iomanip>

using namespace std;

using ll = long long;

#define mtest for (cin >> t; t; -- t)

const int kMaxN = -1, kInf = (((1 << 30) - 1) << 1) + 1;
const ll kLInf = 9.22e18;

string s;
int a = 0, b = 0;

int main() {
  ios::sync_with_stdio(0), cin.tie(0), cout.tie(0);
  cin >> s;
  for (int i = 0; i < s.size(); ++ i) {
    if (s[i] == 48) {
      cout << 1 << ' ' << a + 1 << '\n';
      ++ a, a %= 4;
    } else {
      cout << 4 << ' ' << b + 1 << '\n';
      a += 2, a %= 4;
    }
  }
  return 0;
}

```

---

## 作者：__1d0h8dp__ (赞：0)

~~此题乃黄题中大水题也！~~

## 题目分析

根据题意，我们不难看出，我们可以把竖着放的格子放进第一列，横着的格子放进第四列，这样就可以避免重叠的情况了

为什么呢？因为我们可以看出，竖着的一列一列放，每当四列用光时便会把所有的方格给消掉。

一开始，所有格子都是空的：

![](https://cdn.luogu.com.cn/upload/image_hosting/kwvwfu7v.png)
然后，我们开始一列一列放方格：
![](https://cdn.luogu.com.cn/upload/image_hosting/usnnrzou.png)
![](https://cdn.luogu.com.cn/upload/image_hosting/m235kyed.png)
![](https://cdn.luogu.com.cn/upload/image_hosting/kuq3zqhd.png)

![](https://cdn.luogu.com.cn/upload/image_hosting/wlq8skq9.png)

然后，又空了
![](https://cdn.luogu.com.cn/upload/image_hosting/kwvwfu7v.png)

横的方格同理，放在第四排
![](https://cdn.luogu.com.cn/upload/image_hosting/9qw0ecst.png)
![](https://cdn.luogu.com.cn/upload/image_hosting/tnrg6pyg.png)

最后，也空了
![](https://cdn.luogu.com.cn/upload/image_hosting/kwvwfu7v.png)

**所以，我们只需要竖着的跟横着的分开来放就行了**

## 话不多说，上代码

```
#include<bits/stdc++.h>
using namespace std;
#define int long long
#define itn int
typedef unsigned long long sln;

signed main(){
	string s;
	int x1;int x2;
	getline(cin,s);
	x1=1; //遍历竖着的位置
	x2=1; //横着的位置
	for(int i=0;i<s.length();i++){
		if(s[i]=='0'){ //如果为竖着放的
			cout<<"1 "<<x1;
			x1++;
			if(x1>4){
				x1=1;//消除一排
			}
		}
		else{
			cout<<"4 "<<x2;
			x2+=2; //横着的坐标占两格
			if(x2>4){
				x2=1; //消除一排
			}
		}
		cout<<endl; 
	}
	cout<<endl;
	return 0;
}
```

---

## 作者：wind_whisper (赞：0)

## $\text{Description}$
你有一个 $4\times4$ 的棋盘和一些 $1\times2$ 大小的方格，给你放入的顺序，$0$ 表示竖着放，$1$ 表示横着放，每当一行或一列全放满时会将这一行或列上的消除，输出任意一种使小方格不重叠的方案。
## $\text{Solution}$
似乎和其他题解的方法不太一样。  
竖着的先放 $(1,1)$，再放 $(3,1)$ 把上一个消掉。  
横着的先放 $(4,3)$，再放 $(4,1)$ 把上一个消掉。  
永远不会有冲突。 
## $\text{Code}$
```cpp
#include<bits/stdc++.h>
using namespace std;
#define ll long long
const int N=1e5+100;
inline ll read(){
	ll x(0),f(1);char c=getchar();
	while(!isdigit(c)){if(c=='-')f=-1;c=getchar();}
	while(isdigit(c)){x=(x<<1)+(x<<3)+c-'0';c=getchar();}
	return x*f;
}
int n;
int a,b;
char s[N];
int main(){
	scanf(" %s",s+1);n=strlen(s+1);
	for(int i=1;i<=n;i++){
		if(s[i]=='0'){
			if(a) printf("3 1\n");
			else printf("1 1\n");
			a^=1;
		}
		else{
			if(b) printf("4 1\n");
			else printf("4 3\n");
			b^=1;
		}
	}
}
```


---

