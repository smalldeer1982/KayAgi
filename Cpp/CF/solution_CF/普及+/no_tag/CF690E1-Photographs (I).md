# Photographs (I)

## 题目描述

Heidi 组建的人牛联盟建造了一个防止僵尸攻击的基地, 基地的入口有一个安全门, 这个门执行一种测试, 它会向进入的人 (牛、僵尸) 展示一张照片，并对人 (牛、僵尸) 询问这张照片的上半部分和下半部分是否被交换。人（牛）会认真回答这样的问题； 而僵尸会随便按下两个按钮中的一个。人 (牛、僵尸) 会被询问数次, 如果正确的数量达到或超过 $75$ 个 ，则通向基地的门打开, 否则，通向死亡的门打开。

Heidi 正在组建能消灭僵尸的机器人军队, 她希望你能帮她完成机器人区分图像的功能。

![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF690E1/5049ba9bbfc4129520c0662372ea952b95839547.png)

这是测试所用的图片集的前两张，第一张的上下交换过，但第二张并没有。

## 说明/提示

[下载链接](http://assets.codeforces.com/files/690/easy_contestant_package.zip)

# 题解

## 作者：LLLLLL7381 (赞：0)

~~你谷敢搬运这个题目我就敢交题解。~~                 
## 题目大意
这是个提交答案题，给了你若干张黑白相片的灰度数据，其中部分照片经过了从中间切分并且上下交换。希望你对于每张照片给出是否经过了交换，正确率达到 $75\%$ 以上就可以得满分。其中你需要处理的数据已经给出。
## 思路分析
我们可以先访问[这个](http://assets.codeforces.com/files/690/easy_contestant_package.zip)把样例下载下来。            
在资源管理器找到下载的压缩包并且解压，Windows 下解压文件的方法可以参考[这里](https://support.microsoft.com/zh-cn/windows/%E5%8E%8B%E7%BC%A9%E5%92%8C%E8%A7%A3%E5%8E%8B%E7%BC%A9%E6%96%87%E4%BB%B6-f6dde0a7-0fec-8294-e1d3-703ed85e7ebc)。                  
~~说了一堆废话。~~             
我们看到，解压得到了 $5$ 个文件。
![](https://github.com/UsamiRenko7381/picx-images-hosting/raw/master/屏幕截图-2024-10-21-171027.5mnswnrvbz.webp)
打开倒数两个文件夹中的任意一个，多打开几个图像文件，简单看一下这些文件。
![](https://github.com/UsamiRenko7381/picx-images-hosting/raw/master/屏幕截图-2024-10-21-171555.2a532aifqf.webp)
像上面这个，建筑主体被直接切分了，原本图片的下方被很生硬地与原先图片的上方被拼接到了一起，因此在图片的一半处产生了较大的差异。由于图片的分辨率相对较高，所以如果图片被从中间切开，切开的位置的灰度差异其实可以忽略不计，然而拼接后图片中央的差异会变得很大。其实这道题目完全不用担心被 HACK，因为你有 $25 \%$ 的容错率。                        
所以我们只需要维护图片第一行，最后一行，第 $\lfloor {\frac{n}{2}} \rfloor$ 行和第 $\lfloor {\frac{n}{2}} \rfloor+1$ 行的灰度差异。         
如果图像被切分过，那么中央的灰度差异明显大于第一行和第 $n$ 行的灰度差异。因为经过了交换，第一行和最后一行的灰度差异会大大减小。反之则没有被交换过。
## 代码如下
```c
#include<stdio.h>
int a[610][610];
int abs(int x)
{
    if(x<0)
    {
        return -x;
    }
    return x;
}
int read()
{
   int x=0,f=1;
   char ch=getchar();
   while(ch<'0'||ch>'9')
   {
       if(ch=='-')
           f=-1;
       ch=getchar();
   }
   while(ch>='0' && ch<='9')
       x=x*10+ch-'0',ch=getchar();
   return x*f;
}
void write(int x)
{
    if(x<0)
        putchar('-'),x=-x;
    if(x>9)
        write(x/10);
    putchar(x%10+'0');
    return;
}
int main(void)
{
    freopen("sample.in","r",stdin);
    freopen("sample.out","w",stdout);
    int __=read();
    while(__--)
    {
        int n=read(),m=read();
        for(int i=1;i<=n;i++)
        {
            for(int j=1;j<=m;j++)
            {
                a[i][j]=read();
            }
        }
        int cnt1=0,cnt2=0;
        for(int i=1;i<=m;i++)
        {
            cnt1+=abs(a[1][i]-a[n][i]);
            cnt2+=abs(a[n>>1][i]-a[(n>>1)+1][i]);
        }
        if(cnt1>cnt2)
        {
            puts("NO");
        }
        else
        {
            puts("YES");
        }
    }
    return 0;
}
```

---

## 作者：Sine_Func (赞：0)

# [CF690E1](https://www.luogu.com.cn/problem/CF690E1)

很有意思的一道题。

## 题意

给出一张黑白照片的灰度值，有时图片会从中间分割并交换上下部分，判断是否被交换过。正确率达到 $75\%$ 即可 AC。

## 做法

正常的图片一般颜色不会有太大的跨度，我们只需要对图片的第一行与最后一行 （交换前的第 $n/2$ 行和第 $n/2+1$ 行），第 $n/2$ 行与第 $n/2+1$ 行分别求出差距并相加，判断差距的大小即可。

## code

```cpp
#include <bits/stdc++.h>
#define int long long
using namespace std;
int t, n, m, a[610][610], x, y;
signed main() {
	ios::sync_with_stdio(0);
	cin.tie(0);
	cin >> t;
	while (t--) {
		cin >> n >> m;
		for (int i = 1; i <= n; i++) {
			for (int j = 1; j <= m; j++) {
				cin >> a[i][j];
			}
		}
		x = y = 0;
		for (int i = 1; i <= m; i++)
			x += abs(a[1][i] - a[n][i]);
		for (int i = 1; i <= m; i++)
			y += abs(a[n / 2][i] - a[n / 2 + 1][i]);
		if (x > y)cout << "NO\n";
		else cout << "YES\n";
	}
	return 0;
}
```

[AC](https://codeforces.com/contest/690/submission/284185715)。

---

## 作者：loser_seele (赞：0)

题目大意：给定一个图像的灰度值，问该个图像是否经过上下翻转。达到一定正确率即可通过。

一道有意思的水题。

显然，如果经过翻转，则中间两行和边缘两行的灰度值的方差会变大。

于是检查这四行的灰度值的方差，如果翻转后方差更小则已经翻转过，否则图像没有被翻转。

注意本题读入数据量较大，所以需要一定程度的优化（不过关闭流同步即可通过）。

代码：

```cpp
#include <bits/stdc++.h>
using namespace std;
#define int long long
int p[2020][2020];
int h,w;
int s(int x)
{
    return x*x;
}
int check(int r1,int r2)
{
    int res=0;
    for(int i=1;i<=w;i++)
    res+=s(p[r1][i]-p[r2][i]);
    return res;
}
signed main()
{
    ios::sync_with_stdio(0);
    int T;
    cin>>T;
    while(T--)
    {
        cin>>h>>w;
        for(int i=1;i<=h;i++)
        for(int j=1;j<=w;j++)
        cin>>p[i][j];
        if(check(1,h)<check(h/2,h/2+1))
        cout<<"YES"<<'\n';
        else
        cout<<"NO"<<'\n';
    }
}
```


---

## 作者：DPseud (赞：0)

[题目传送门](https://www.luogu.com.cn/problem/CF690E1)

### 题目大意

给出一幅黑白图的灰色值，你需要判断它是否经过翻转，这里的翻转指的是把上半部分平移到下半部分（可以理解为一个经典的 splay 操作：把上半部分反转，把下半部分反转，再把整个反转）。

对于一个数据，只需要满足 $75\%$ 的询问能通过就可以了。

### 解题思路

我们逆向想，从“只需要满足 $75\%$ 的询问能通过就可以了”中能看出，没有程序能做到百分百通过，为什么呢？因为我们采用了一种不完全正确的判断方式，那就是判断图的合理性。

正常情况下，一张图是合理的，意味着它是渐变的，也就是说，图的大多数部分都是相邻的两个色块颜色（即题目中的灰色值）相近，一张图没那么合理时就意味着大多数的相邻色块灰色值相差较大。

但是，“较大”、“相近”如何定义？这就需要翻转图和原图的对比了。

所以我们可以把图翻转，判断前者和后者哪个相邻色块灰色值差总体更小。

这个思路还不是最简便的，这是因为后者仅仅相比前者多了最上面和最下面之间的相差，但是同时也少了中间两行之间的相差，所以我们可以直接判断哪个相差小，中间两行相差小，则没有翻转，否则有。

### 码码

```cpp
#include<bits/stdc++.h>
using namespace std;
int main()
{
    static int q,n,m,a[2222][2222];
    cin>>q;
    while(q--)
    {
		cin>>n>>m;
		for(int i=1;i<=n;i++)
		{
			for(int j=1;j<=m;j++)scanf("%d",bitand a[i][j]);
		}
		int d1=0,d2=0;
		for(int j=1;j<=m;j++)
		{
			d1+=(a[1][j]-a[n][j])*(a[1][j]-a[n][j]);
			d2+=(a[n/2][j]-a[n/2+1][j])*(a[n/2][j]-a[n/2+1][j]);
		}
		if(d2<d1)puts("NO");
		else puts("YES");
	}
    return 0;
}
```


---

