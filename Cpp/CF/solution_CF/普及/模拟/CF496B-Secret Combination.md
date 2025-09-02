# Secret Combination

## 题目描述

You got a box with a combination lock. The lock has a display showing $ n $ digits. There are two buttons on the box, each button changes digits on the display. You have quickly discovered that the first button adds 1 to all the digits (all digits 9 become digits 0), and the second button shifts all the digits on the display one position to the right (the last digit becomes the first one). For example, if the display is currently showing number 579, then if we push the first button, the display will show 680, and if after that we push the second button, the display will show 068.

You know that the lock will open if the display is showing the smallest possible number that can be obtained by pushing the buttons in some order. The leading zeros are ignored while comparing numbers. Now your task is to find the desired number.

## 样例 #1

### 输入

```
3
579
```

### 输出

```
024
```

## 样例 #2

### 输入

```
4
2014
```

### 输出

```
0142
```

# 题解

## 作者：HoshizoraZ (赞：2)

这道题其实想出了枚举方法就不是很难了。

枚举，需要条理清晰，不重不漏。

那怎么样才能不重不漏呢？

我们试着这样想：能不能先把其中一种操作做完，再去做另一种操作呢？

那么，就可以开始尝试了：

以 $579$ 为例：

我们先移动数位，可以得到三种结果：$579,957,795$

然后再分别在这三个数上面进行讨论。

讨论 $579$：

我们如果要字典序最小，那么应该怎么加呢？

**让第一位变成 0！**

没错，字典序永远先管高位。

我们只要确定了第一位是 $0$，那么整个新字符串就确定了。

如果 $579$ 第一位变成了 $0$，那么肯定是进行了 $10-5=5$ 次加法操作。

因此让后面的位数都加上 $5$ 再取模 $10$ 即可。

最后再从这几个字符串中找出字典序最小的就可以了。

代码如下：

```cpp
#include <cstring>
#include <cstdio>

int n;
char s1[1010], s2[1010], ans[1010];

void solve(){
	int las = 10 - (s2[0] - '0');	//注意这是字符，所以要先将字符变成数字
	s2[0] = '0';
	for(int i=1; i<n; i++)
		s2[i] = (s2[i] - '0' + las) % 10 + '0';	//然后再将数字变成字符
        
	if(strcmp(s2, ans) < 0)			//比字典序小，即答案更优
		strcpy(ans, s2);			//更换答案
}

int main(){
	
	scanf("%d %s", &n, s1);
	for(int i=0; i<n; i++)			//初始化答案数组
		ans[i] = 'a';
        
	for(int i=0; i<n; i++){
		for(int j=i; j<i+n; j++)		//枚举字符串，注意位数要取模
			s2[j - i] = s1[j % n];
		solve();
	}
	puts(ans);

	return 0;
}
```

---

## 作者：ztytql (赞：2)

[题目传送门](https://www.luogu.com.cn/problem/CF496B)
## Description
给定一个数字字符串，有两种操作：将字符串所有字符右移一位或将字符串所有字符加一，求经过若干次操作后得到字典序最小的字符串。

## Solution
对于将字符串右移一位，我们可以将两个相同字符串拼接起来，这个可以用字符串的特性 ```str += str``` 来很轻松的完成循环右移操作，读者可以自行理解一下。

对于枚举所有的可能情况，我们可以在每次枚举中将整个字符串使用 ```string``` 库中的函数 ```substr(start,len)``` （其中 ```start``` 表示起始位置的下标， ```len``` 表示截取的长度）将字符串分割，然后循环枚举从 $0$ 到 $9$ 的每一次加数，最后每次判断最小字典序即可，这可以直接用比较运算符来完成。

具体详见代码。
## Code
```cpp
#include <bits/stdc++.h>
using namespace std;

string s, ans = "1"; // ans 为最终字典序最小的字符串，其首位设置为 1 保证了较大的字典序，使得最小的字典序不是 ans 的初始值。
int n;

int main()
{
	cin >> n >> s;
	
	s += s; // 将 s 扩展一倍，以进行循环右移操作 
	
	for (int i = 0 ; i < n ; i ++ ) // 循环枚举右移的位数 
	{
		string cnt = s.substr(i, n); // 切割一个起始点为 s[i], 长度为 n 的字符串 
		for (int j = 0 ; j <= 9 ; j ++ ) // 循环枚举操作二 
		{
			for (int k = 0 ; k < n ; k ++ )
				if (cnt[k] == '9')
					cnt[k] = '0';
				else
					cnt[k] ++;
			if (ans > cnt) // 取字典序最小的字符串 
				ans = cnt;
		}
	}
	cout << ans << endl;
	
	return 0;
}
```

---

## 作者：H2O_TX (赞：1)

本蒟蒻的第一篇题解。

这道题题意就不用过多描述了。

一开始要注意到字典序的特性，就是首先比较高位，那么我们必须让第一位为 $0$。

接下来，我们考虑让哪一个数字变成 $0$，由于数据范围极小（$1\le n \le 1000$），我们可以直接枚举每一位数字。

在确定了这个数字后，每位数字的值就都确定了，这里模拟题意即可。

最后注意比较的时候按字典序比较（本人写题时没用草稿纸这里搞错了好几遍）。

个人认为这个思路非常简单。~~不知道为啥是蓝题~~

贴代码（带注释）：

```cpp
#include<bits/stdc++.h>
using namespace std;

const int N = 1009;
int n;
string s;
int ans[N],temp[N];//ans 是最终答案，temp是每次枚举时生成的新序列。

int main()
{
    cin>>n>>s;
    ans[0]=9;//初始化，否则会直接输出000...
    for(int i=0;i<n;i++)
    {
        int delta=10-s[i]+'0';//差量，表示要使当前枚举的这位变成0需要加上多少个1
        for(int j=0;j<n;j++) temp[j]=(s[j]-'0'+delta)%10;//按照题意模拟
        int fl=0;
        for(int j=i,k=0;k<n;k++,j++,j%=n)//对temp的枚举要从i开始，这样就把0放到了第一位。下同
        {
            if(ans[k]==temp[j]) continue;
            if(ans[k]>temp[j]) fl=1;
            break;
        }
        if(fl) for(int j=i,k=0;k<n;k++,j++,j%=n) ans[k]=temp[j];
    }
    for(int i=0;i<n;i++) cout<<ans[i];
    return 0;
}

```


---

## 作者：ATION001 (赞：0)

## 思路
我们先断环为链（方便处理），然后枚举最高位，将其变成 $0$。

随后将后面的字符都加上 $10-a_1$，对 $10$ 取模。

将所有情况取字典序最小的情况即可。

时间复杂度 $O(n^2)$，不过也能过。
## 代码
```cpp
#include<bits/stdc++.h>
using namespace std;
char a[2010];
string ans="";
int n;
int main(){
	ios::sync_with_stdio(0),cin.tie(0),cout.tie(0);
	cin>>n;
	for(int i=1;i<=n;i++){
		cin>>a[i];
		a[i+n]=a[i]; // 断环为链
		ans+="9999"; // 初始化为极大值
	}
	for(int i=1;i<=n;i++){
		string s="";
		// 将开头变成 0 后取字典序最小的序列
		int y=(10-(a[i]-'0'))%10;
		for(int j=i;j<i+n;j++){
			s+=to_string((y+(a[j]-'0'))%10);
		}
		ans=min(ans,s);
	}
	cout<<ans;
	return 0;
}
```

---

## 作者：Loser_Syx (赞：0)

显然操作顺序对答案并不影响，且操作二总是以 $10$ 次唯一循环，故可以先枚举操作二进行了几次，然后直接暴力选择最小字符串。  
具体地说，先算出加完操作二的字符串，然后直接暴力将首添加至尾即可。

```
signed main() {
	int n = read();
	string s; cin >> s;
	string ans = s;
	for (int i = 0; i < 10; ++i) {
		string now = s;
		for (int j = 0; j < n; ++j) {
			now[j] += i;
			if (now[j] > '9') now[j] -= 10;
		}
		for (int j = 0; j < n; ++j) {
			now.push_back(now.front());
			now.erase(now.begin());
			ans = min(ans, now);
		}
	}
	cout << ans << '\n';
	return 0;
} 
```

---

## 作者：_JF_ (赞：0)

## CF496B Secret Combination

你说的对，但是转眼之间，又要月考了。

来一个 $O(n)$ 的做法。

首先发现两个操作是没有互相影响的，就把他们分开来看。

如果先进行操作二的话，发现只会至多进行 $10$ 次，这个字符串就会变成原来的样子，所以我们就只做 $10$ 次。

每一次加完后，在这个基础上找最小，相当于把这个字符串看成一个环，从某一个位置开始走一圈，实际上就是找这个字符串的最小表示法。这就只用 $O(n)$ 的时间。

那对 $10$ 种情况取最小即可。

当然还有一种做法就是，先看 $1$ 操作，再看 $2$ 操作，那就是钦定字符串的任意一个位置变为第一个字符，然后让他变成 $0$ 取最小，不过这样是 $O(n^2)$ 的了。

```cpp
#include<bits/stdc++.h>
using namespace std;
const int N =1e6+10;
char s[N],S[N];
int n;
bool vis=false;
string ans;
void Slove(string k){
	for(int i=0;i<k.length();i++)
		S[i+1]=S[i+n+1]=k[i];
	int i=1,j=2;
	while(i<=n&&j<=n){
		int k=1;
		while(S[i+k-1]==S[j+k-1]&&k<=n)	k++;
		if(k>n)	break;
		if(S[i+k-1]<S[j+k-1])	j=j+k;
		else	i=i+k;
		if(i==j)	j++;
	}
	int num=min(i,j);
	string num1;
	for(int len=1;len<=n;len++)	num1+=S[num+len-1];
	if(vis==false){
		vis=true,ans=num1;
		return ;
	}
	ans=min(ans,num1);
	return ;
}
int main(){
	cin>>n;
	scanf("%s",s+1);
	for(int num=0;num<=9;num++){
		string k;
		for(int i=1;i<=n;i++){
			k+=char((int(s[i]-'0')+num)%10+'0');
		}
		Slove(k);
	}	
	cout<<ans<<endl;
}
```


---

## 作者：Register_int (赞：0)

$n\le1000$，明显可以暴力。  
把每个轮换的结果拉下来，把开头加成 `'0'`，最后找字典序最小的就可以了。  
懒得写字符串比较，这里用的是 `string`。
# AC 代码
```cpp
#include <bits/stdc++.h>

using namespace std;

const int MAXN = 1e3 + 10;

int n;

string s[MAXN], ans;

int main() {
	cin >> n >> s[0];
	for (int i = 1; i < n; i++) {
		for (int j = 0; j < n; j++) s[i] += (s[0][(j + i) % n] - s[0][i] + 10) % 10 + '0';
	}
	for (int i = 1; i < n; i++) s[0][i] = (s[0][i] - s[0][0] + 10) % 10 + '0';
	s[0][0] = '0', ans = s[0];
	for (int i = 1; i < n; i++) ans = min(ans, s[i]);
	cout << ans;
}
```

---

## 作者：nydzsf_qwq (赞：0)

# CF496B Secret Combinatio

## 题目大意

给一个点位数为 $n$ 的数字，支持两种操作：

$1$：将每个数字右移一位，最后一位移到第一位。

$2$：将每个数字加 $1$，$9$ 变成 $0$（翻译错了，不过看样例可以看出来）。

## 题解

首先，我们发现改变操作的顺序是不影响结果的，做 $n$ 次操作 $1$ 和不操作是没有区别的。

因此可以让所有不超过 $n-1$ 次操作1先进行，之后再进行操作 $2$。

枚举操作 $1$ 进行的次数，在操作1次数一定的情况下显然将第一个数字变成 $0$ 的情况下最小。

将这种情况下的最小值与记录最小值比较并将较小值记录即可。

时间复杂度 $O(n^2)$。

### Code

``` cpp
#include<bits/stdc++.h>
using namespace std;
int n,tmp;
bool bl;
char s[1005],ans[1005];
int main() {
	scanf("%d",&n);
	scanf("%s",s+1);
	for(int i=1;i<=n;++i) ans[i]=(s[i]-s[1]+10)%10;
	for(int i=2;i<=n;++i) {
		bl=0;
		for(int j=0;j<n;++j) {
			tmp=(s[(i+j-1)%n+1]-s[i]+10)%10;
			if(tmp<ans[j+1]) bl=1;
			if(bl) ans[j+1]=tmp;
			else if(tmp>ans[j+1]) break;
		}
	}
	for(int i=1;i<=n;++i) printf("%c",ans[i]+'0');
	return 0;
}
```



---

## 作者：Arghariza (赞：0)

- Solution 

每个数字加一不影响数字顺序。

所以直接枚举 $S_i,i\in\{1,2,...,n\}$ 在开头的情况，然后直接把 $S$ 每个元素加到首位为 $0$ ，与已知的答案串字典序比较即可。

$O(n^2)$

- 优化：

在暴力枚举开头的做法的基础上来一个指针 $k$ ，指向**此时数列首元素的下标**，将 $S_{n+1}\to S_{2n}$ 将前面的 $S_1\to S_{n}$ 复制一遍，然后从 $S_k\to S_{k+n-1}$ 进行字典序比较即可。

仍是 $O(n^2)$ ，但按理说常数会小一些（（

~~当然这常数小和不小都能过~~

如果您懒得打比较字典序的话可以先记录下来，后面再 $O(n\log n)$ 给它排序一遍。

[$\mathtt\color{lightgreen}AC\ Code$](https://www.luogu.com.cn/paste/k43njsua)

---

## 作者：Level_Down (赞：0)

### 题意简述：

给定一个字符串 s，可以将它每一位都向后移（最后一位到第一位），也可以将每一位的数都加一（注意：9 会变成 0 ，应该是翻译的锅），问最后 s 能变成的字典序最小的数是什么？

### 方法：

好吧，我的思路是从楼上巨佬来的，但是做法有不同，适合新手看（没错，我就是一个新手）

主要思路是枚举，先利用操作1将 s 变成可能出现的每一种情况，这里拿样例二举个例子：

2014 可能变成 2014 、 0142 、 1420 、4201 这四种

然后利用操作二将这四种情况的字典序最小值求出来，即让最高位为0：

2014 → 0892 ； 0142 → 0142 ； 1420 → 0319 ； 4201 → 0867

然后就可以直接 sort ，输出答案。

代码：

```cpp
#include <bits/stdc++.h>
using namespace std;
int n,cnt;//cnt在操作一中当指针用，在操作二中当做每个数需要增加的那个数值
string s,a[1005];//a存放被操作的字符串
int main()
{
	cin >> n >> s;
	for (int i = 1; i <= n; i++)//操作一
		{
			cnt = i - 1;//每次从不同的地方开始
			for (int j = 1; j <= n; j++)
				{
					if (cnt == n) cnt = 0;//超出长度，从头来
					a[i] += s[cnt];//存入
					cnt++;//指针右移
				}
		}	
	for (int i = 1; i <= n; i++)//操作二
		{
			cnt = '9' - a[i][0] + 1;//每个数需要增加的数值
			for (int j = 0; j < n; j++)
				{
					a[i][j] += cnt;//增加
					if (a[i][j] > '9') a[i][j] -= 10;//如果超出9，减10
				}
			}	
	sort(a+1,a+1+n);//愉快的快排
	cout << a[1] << endl;//输出最小的那个			
	return 0;//AC！
}
```


---

