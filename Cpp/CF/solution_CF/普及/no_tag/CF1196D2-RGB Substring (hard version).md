# RGB Substring (hard version)

## 题目描述

The only difference between easy and hard versions is the size of the input.

You are given a string $ s $ consisting of $ n $ characters, each character is 'R', 'G' or 'B'.

You are also given an integer $ k $ . Your task is to change the minimum number of characters in the initial string $ s $ so that after the changes there will be a string of length $ k $ that is a substring of $ s $ , and is also a substring of the infinite string "RGBRGBRGB ...".

A string $ a $ is a substring of string $ b $ if there exists a positive integer $ i $ such that $ a_1 = b_i $ , $ a_2 = b_{i + 1} $ , $ a_3 = b_{i + 2} $ , ..., $ a_{|a|} = b_{i + |a| - 1} $ . For example, strings "GBRG", "B", "BR" are substrings of the infinite string "RGBRGBRGB ..." while "GR", "RGR" and "GGG" are not.

You have to answer $ q $ independent queries.

## 说明/提示

In the first example, you can change the first character to 'R' and obtain the substring "RG", or change the second character to 'R' and obtain "BR", or change the third, fourth or fifth character to 'B' and obtain "GB".

In the second example, the substring is "BRG".

## 样例 #1

### 输入

```
3
5 2
BGGGG
5 3
RBRGR
5 5
BBBRR
```

### 输出

```
1
0
3
```

# 题解

## 作者：GeraldG (赞：7)

题意：

有个“RGB”无限循环的长母串，q组样例，每组一个n长的字符串，让你通过更改n长串的某个字符构造一个长度为k的，既是母串的子串，也是n长串的子串。求满足要求的最少更改次数。

思路：

母串t：BGGGG（3种）
样串s：RBGRBGRBGRBGRBGRBG
贡献a：11011 (不同的话，在这一位的贡献就是1，这个也是3种)

然后因为的们要获得区间长度为K的最小贡献，所以求个a的前缀和
O(1)遍历每一个长度为K的子串，找出最小的那个就是ans

 

```cpp
#include<iostream>
#include<cstring>
using namespace std;
const int M=2e5+10;
char s[M];
int a[3][M];
int T,n,k,ans;
int main() {
    cin>>T;
    while(T--) {
        a[0][0]=a[1][0]=a[2][0]=0;
        cin>>n>>k;
        cin>>s;
        ans=M;
        string t="RGB";
        for(int i=0; i<n; i++) {
            for(int j=0;j<=2;j++){
                if(s[i]!=t[(i+j)%3])a[j][i+1]=a[j][i]+1;
                else a[j][i+1]=a[j][i];
            }
        }//a从下标为1的位开始&前缀和
        for(int i=0; i+k<=n; i++) {
            for(int j=0;j<=2;j++){
                ans=min(ans,a[j][i+k]-a[j][i]);
            }
        } //遍历求ans
        cout<<ans<<endl;
    }
    return 0;
}
```


---

## 作者：heyx0201 (赞：3)

# RGB Substring (hard version) 题解
## 思路
首先观察得出：字符串 $s$ 的长度为 $k$ 子串为 `RGBRGBRGB......` 的子串，这个子串只有三种可能：`RGBRGBRGB......`，`GBRGBRGBR......`，`BGBRGBRG......`。

所以自然可以想出一种 $O(n^2)$ 的解法：先枚举 $3$ 种情况，然后再枚举左端点和右端点，但是这么做是无法通过此题的。因为此题 $n \le 2 \cdot 10^5$。

但我们可以双指针枚举两个端点，同向移动，每次加上后面的字符，去掉前面的字符，然后判断。这么做时间复杂度是线性的，因为每个字符都只会被两个指针各扫描一次。 

时间：双指针枚举左右两个端点，$O(n)$，总时间 $O(n)$。
## AC Code
```cpp
#include<iostream>
#include<algorithm>

using namespace std;

const string kPos = "RGB";

int q,n,k;
string s;

void Solve(){
  cin >> n >> k >> s;
  int ans = n;
  for (int p = 0; p < 3; p++){
    int sum = 0;
    for (int i = 0; i < n; i++){
      sum += s[i] != kPos[(p + i) % 3];
      if (i + 1 >= k){
        ans = min(ans,sum);
        sum -= s[i - k + 1] != kPos[(p + i - k + 1) % 3];
      }
    }
  }
  cout << ans << '\n';
}

int main(){
  ios::sync_with_stdio(0);
  cin.tie(0); cout.tie(0);
  cin >> q;
  while (q--){
    Solve();
  }
  return 0;
}

```

---

## 作者：fjy666 (赞：3)

## 0x01 思路
首先从 RBG 串的性质入手。  
发现当长度为 $n$ 时，有且只有三种 RGB 串：
- `RGBRGBRGB......`
- `GBRGBRGBR......`
- `BRGBRGBRG......`

我们只要枚举这三种串，再和原串对比，求操作次数就 OK 了！  

## 0x02 代码
```cpp
#include <algorithm>
#include <cstdio>
#define _for(i_,a_,b_) for(int i_ = a_;i_ < b_;++i_)
#define _rep(i_,a_,b_) for(int i_ = a_;i_ <= b_;++i_)
typedef long long ll;
int n,k,ans = 0x7fffffff;
char s[200050];
const char str[] = "RGB";
inline void getNxt(int& qwq){qwq = (qwq+1) % 3;}
void solve(int fjy){
	int cnt = 0;
	_rep(i,1,k){
		if(s[i] != str[fjy])++cnt;
		getNxt(fjy);
	}
	char *st = s+1,*ed = s+k;
	while(*ed != '\0'){
		ans = std::min(ans,cnt);
		if((*st) != str[((fjy-k)%3+3)%3])--cnt;
		++st;++ed;
		if(*ed != str[fjy])++cnt;
		getNxt(fjy);
	}
}

void solve(void){
	scanf("%d%d",&n,&k);
	scanf("%s",s+1);
	ans = 0x7fffffff;
	solve(0);
	solve(1);
	solve(2);
	printf("%d\n",ans);
}

int main(){
	int T;
	scanf("%d",&T);
	while(T--){
		solve();
	}
    return 0;
}
```

---

## 作者：EatBread (赞：0)

这道题很简单，第一眼就想到分为。

RGB 的循环，GBR 的循环，BRG 的循环枚举，然后程序就出来了，但是我一提交，超时了。

于是，我想到，是不是可以用类似尺取法的思路呢？因为这样，可以省掉一个循环。

但是，由于爆枚是分为三个循环，依次判断三种情况，也就是这样：

```
5 3 
BGRGG
RGBRGBRGB......

BGR RGB------2
GRG RGB------3
RGG RGB------1
mi=1

```
而尺取是这样：

```
5 3 
BGRGG
RGBRGBRGB......

BGR RGB------2
GRG GBR------2
RGG BRG------2
mi=2

```
显然现在是不行，可如果是 GBR 的循环：

```
5 3 
BGRGG
GBRGBRGBR......

BGR GBR------2
GRG BRG------1
RGG RGB------1
mi=1

```
也就是说，如果尺取也是枚举三种情况的话，也是可行的。
```cpp
#include<bits/stdc++.h>
using namespace std;
int n,a,b,gs;
string s;
char h[3];
int js()
{
	int t=0,mi=10000000,w=b;
	int ans=0;
	for(int i=t; i<w; i++){if(s[i]!=h[(i-t)%3])ans++;}mi=min(ans,mi);
	while(w<=a)
	{
		if(s[t]!=h[t%3])ans--;
		if(s[w]!=h[w%3])ans++;
		mi=min(mi,ans);
		t++,w++;
	}
	return mi;
}
int main()
{
	cin>>n;
	for(int i=1; i<=n; i++)
	{
		scanf("%d%d",&a,&b);cin>>s;gs=10000000;
		h[0]='R',h[1]='G',h[2]='B';gs=min(gs,js());
		h[0]='G',h[1]='B',h[2]='R';gs=min(gs,js());
		h[0]='B',h[1]='R',h[2]='G';gs=min(gs,js());
		printf("%d\n",gs);
	}
	return 0;
} 

```




---

