# [NEERC 2014] Alter Board

## 题目描述

小 Dima 给了他的小弟弟 Petya 一个大小为 $n \times m$ 的交互式棋盘作为礼物。这个棋盘有很多很棒的功能，但有一个是 Petya 最喜欢的。他可以选择由棋盘方格形成的任意矩形并进行反转。被反转矩形中的每个白色单元格变为黑色，每个黑色单元格变为白色。

在初始状态下，棋盘是以国际象棋风格着色的，即每个单元格要么是黑色，要么是白色，并且每两个共享一条边的单元格具有不同的颜色。小 Petya 想执行上述几个反转操作以将所有单元格变为相同的颜色。他很不耐烦，所以他请你提供指令，以最少的反转次数完成。

## 说明/提示

时间限制：1 秒，内存限制：256 MB。

特殊评测提供者：@[shenyouran](/user/137367)。

题面翻译由 ChatGPT-4o 提供。

## 样例 #1

### 输入

```
2 2
```

### 输出

```
2
1 1 1 1
2 2 2 2
```

# 题解

## 作者：indream (赞：2)

## P6985 \[NEERC2014] Alter Board 题解
[P6985](https://www.luogu.com.cn/problem/P6985) | [AC](https://www.luogu.com.cn/record/139628837)
### 思路
很神奇。

这是一个棋盘：（$n=m=7$）
```
0101010
1010101
0101010
1010101
0101010
1010101
0101010
```
贪心考虑让每次翻转中同色的尽可能多，即“副作用”尽量小。

方法：可以先把每个**偶数行**整行翻转，得到下面的棋盘：
```
0101010
0101010
0101010
0101010
0101010
0101010
0101010
```
接下来干什么大家到知道：把所有**偶数列**整列翻转即可。

> 为什么是偶数行，偶数列？

当 $n,m\bmod2=1$ 时显然有优势：比如行，翻奇数列翻 $n\div2+0.5$ 次，而翻偶数列要少 $1$ 次。

最终显然要 $n/2+m/2$ 次（**向下取整**）。

代码实现只需模拟即可。
### 代码
```cpp
#include<bits/stdc++.h>
using namespace std;
int n,m;
int main(){
    cin>>n>>m;
    cout<<n/2+m/2<<'\n';
    for(int i=2;i<=n;i+=2)
        cout<<i<<" 1 "<<i<<' '<<m<<'\n';
    for(int i=2;i<=m;i+=2)
        cout<<"1 "<<i<<' '<<n<<' '<<i<<'\n';
  return 0;
}
```

---

## 作者：Stars_visitor_tyw (赞：1)

## P6985 [NEERC2014] Alter Board 题解
### 分析
我们可以发现棋盘按黑白相间的方式排列。先考虑行，分为只翻转偶数行或只翻转奇数行两种情况，很明显，翻转偶数行答案是最优的，因为若行数为奇数，则奇数行比偶数行多 $1$ 行，翻转次数也比偶数多。再考虑列，一样是反转偶数列次数最少，原因同上，列数也可能为奇数。偶数行有 $\left\lfloor \frac{n}{2} \right\rfloor$ 行，偶数列有 $\left\lfloor \frac{m}{2} \right\rfloor$ 列，当然，C++ 中整数运算会自动向下取整。最后在输出所有偶数行和所有偶数列即可。

### 代码
```cpp
#include<bits/stdc++.h>
#define int long long
using namespace std;
inline int read(){
    int x=0,f=1;
    char ch=getchar();
    while(ch<'0'||ch>'9'){if(ch=='-') f=-1;ch=getchar();}
    while(ch>='0'&&ch<='9'){x=x*10+ch-'0';ch=getchar();}
    return x*f;
}
void write(int x){
    if(x<0){x=-x;putchar(45);}
    if(x>9) write(x/10);
    putchar(x%10+48);
    return;
}
int n, m, ans;
signed main()
{
    ios_base::sync_with_stdio(false);
	n=read();
	m=read();
	cout<<n/2+m/2<<"\n";
	for(int i=2;i<=n;i+=2)
	{
		cout<<i<<" 1"<<" "<<i<<" "<<m<<"\n";
	}
	for(int i=2;i<=m;i+=2)
	{
		cout<<"1 "<<i<<" "<<n<<" "<<i<<"\n"; 
	}
	return 0;
}

---

## 作者：_QyGyQ_ (赞：0)

## 思路
题目要求我们要反转任意矩形，把一个规定大小的国际象棋棋盘转换成同色的。因为棋盘是黑白交错的，所以我们只需要先把偶数列全反转，再把偶数行全部反转，就能将棋盘转换成同色的。之所以不反转奇数行列，是因为当长或宽中有奇数时，奇数行列数会比偶数行列数多一，无法保证最优。
## 代码
```cpp
#include<bits/stdc++.h>
using namespace std;
using ll=long long;
const int N=1e6+7;
int main(){
	int n,m;
	cin>>n>>m;
	cout<<n/2+m/2<<"\n";
	for(int i=1;i<=n;i++){
		if(i%2==0){
			cout<<i<<" "<<1<<" "<<i<<" "<<m<<"\n"; 
		}
	}
	for(int i=1;i<=m;i++){
		if(i%2==0){
			cout<<1<<" "<<i<<" "<<n<<" "<<i<<"\n"; 
		}
	}
	return 0;
} 
```


---

## 作者：yzm0325 (赞：0)

# P6985 [NEERC2014] Alter Board 题解

~~题外话：这其实是我随机跳题时跳到的~~

## 题目大意

给定一个 $n$ 行 $m$ 列的国际象棋棋盘，每次操作可以选择一个矩形区域，将这个区域里所有格子的颜色反转。求最少多少次可以让整个棋盘同色以及操作过程。

## 思路

~~应该没有人不知道国际象棋棋盘长啥样吧~~。这里我画一个棋盘方便理解：

![](https://cdn.luogu.com.cn/upload/image_hosting/ifxvqh72.png)

先考虑如何反转列。我们要尽量把棋盘变成黑白条纹状的，这样只需要再反转一些行就可以做到。于是我们反转所有偶数列：

![](https://cdn.luogu.com.cn/upload/image_hosting/ig8x73bq.png)

接下来只需要再反转所有偶数行就可以了。

有人可能会问：反转奇数列和奇数行不行吗？这样确实也可以，但是在 $n,m$ 中存在奇数时，奇数列（行）的数量会比偶数列（行）的数量多 $1$，如果反转奇数列和奇数行则无法保证是最优的。

得到这个结论后，代码也非常好写，输出 $\lfloor n \div 2 \rfloor+\lfloor m \div 2 \rfloor$，再循环输出操作即可。

## 代码

```cpp
#include <bits/stdc++.h>
using namespace std;
int n, m;
int main() {
    cin >> n >> m;
    cout << n / 2 + m / 2 << '\n'; // C++ 自带向下取整
    for(int i = 2; i <= n; i += 2) // 操作列
        cout << i << ' ' << 1 << ' ' << i << ' ' << m << '\n';
    for(int i = 2; i <= m; i += 2) // 操作行
        cout << 1 << ' ' << i << ' ' << n << ' ' << i << '\n';
    return 0; // 完结撒花！！
}
```

---

## 作者：huangmingyi (赞：0)

#### 分析

![](https://cdn.luogu.com.cn/upload/image_hosting/m0815vtt.png?x-oss-process=image/resize,m_lfit,h_170,w_225)

1. 首先我先画一张图，这是一个 $4 \times 8$ 的矩阵。
2. 第一想法就是每一个都弄一遍。

```
#include<bits/stdc++.h>
using namespace std;
int n,m,ans;
int main(){
	cin>>n>>m;
	ans=(n/2)*m;
	cout<<ans<<endl;
	for(int i=1;i<=n;i+=2){
		cout<<i<<" "<<i<<" "<<i<<" "<<i<<endl;
	}
	for(int i=2;i<=m;i+=2){
		cout<<i<<" "<<i<<" "<<i<<" "<<i<<endl; 
	}
	return 0;
}
```

~~第二点错了~~

3. 于是我开动给我的大脑，于是想到了这样的想法:

![](https://cdn.luogu.com.cn/upload/image_hosting/4nd0oe64.png?x-oss-process=image/resize,m_lfit,h_170,w_225)

4. 把红色的行与紫色的行进行反转，第一次是这样：

![](https://cdn.luogu.com.cn/upload/image_hosting/cz936hlz.png?x-oss-process=image/resize,m_lfit,h_170,w_225)

5. 第二次是这样的：

![](https://cdn.luogu.com.cn/upload/image_hosting/8s6feoop.png?x-oss-process=image/resize,m_lfit,h_170,w_225)

6. 成功反转，开始讲解。
6. 第一次把每偶数行的 $1$ 到 $n$ 的每个格子变白色，再把每偶数列的黑色变白色。
1. 因此只要 $n \div 2 + m \div 2$ 此操作，有的人可能问了，为什么只转黑色的格子？其实应为黑色在末尾，奇数列黑色少，偶数列一样多，奇数行黑色少，偶数行一样多，所以转黑色最少。

```
#include<bits/stdc++.h>
using namespace std;
int n,m,ans;
int main(){
	cin>>n>>m;
	ans=n/2+m/2;
	cout<<ans<<endl;
	for(int i=2;i<=n;i+=2){
		cout<<i<<" "<<1<<" "<<i<<" "<<m<<endl;
	}
	for(int i=2;i<=m;i+=2){
		cout<<1<<" "<<i<<" "<<n<<" "<<i<<endl; 
	}
	return 0;
}
```

---

## 作者：Clarinet (赞：0)

这是一篇鸽了很久的题解，因为这题很长之间内都是不可做的，感谢洛谷官方修改数据！

[更好的食用体验](https://www.luogu.com.cn/blog/Czel-X/ti-xie-18-post)  [原题链接](https://www.luogu.com.cn/problem/P6985)
# 简要题意
题目翻译得十分简要，这里挂一张~~可能不大标准~~的网图国际象棋棋盘，帮助大家理解。
![](https://cdn.luogu.com.cn/upload/image_hosting/vwnov1gw.png)
# 分析
不难看出棋盘是按照黑白相间的方式排列的，而且每个格子旁边都没有相同的颜色。

如果单看行的话，其实所有奇数行都一样，所有偶数行也都一样，那么我们如果翻转所有的偶数行区域，就可以得到以下结果（简化版）：
![](https://cdn.luogu.com.cn/upload/image_hosting/mj6z6p0a.png)
此时就很明确了，再翻转所有偶数列即可。

那么为什么我们选择翻转偶数行列而非奇数行列呢？如果单看结果，可以发现翻转奇数行列结果也是正确的，但举个例子，如果行列数为 $5$ 的话，翻转偶数就会比奇数少，所以我们选择偶数。

最少翻转次数就是 $n/2+m/2$，非常好想，再输出所有偶数行和偶数列即可。
# 代码
```cpp
#include<bits/stdc++.h>
using namespace std;
int n,m,ans;
int main(){
	cin>>n>>m;
	ans=n/2+m/2;
	cout<<ans<<endl;
	for(int i=2;i<=n;i+=2){
		cout<<i<<" "<<1<<" "<<i<<" "<<m<<endl;
	}
	for(int i=2;i<=m;i+=2){
		cout<<1<<" "<<i<<" "<<n<<" "<<i<<endl; 
	}
	return 0;
}
```
# 尾声
第一次写尾声，因为这题对我有点纪念意义。

从今年八月二十四号起，这题我的提交记录就有 $4$ 页，可谓是~~极大浪费评测资源~~十分死磕题目了。

感谢阅读！

---

