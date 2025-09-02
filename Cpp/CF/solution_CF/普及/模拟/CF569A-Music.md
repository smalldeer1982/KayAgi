# Music

## 题目描述

Little Lesha loves listening to music via his smartphone. But the smartphone doesn't have much memory, so Lesha listens to his favorite songs in a well-known social network InTalk.

Unfortunately, internet is not that fast in the city of Ekaterinozavodsk and the song takes a lot of time to download. But Lesha is quite impatient. The song's duration is $ T $ seconds. Lesha downloads the first $ S $ seconds of the song and plays it. When the playback reaches the point that has not yet been downloaded, Lesha immediately plays the song from the start (the loaded part of the song stays in his phone, and the download is continued from the same place), and it happens until the song is downloaded completely and Lesha listens to it to the end. For $ q $ seconds of real time the Internet allows you to download $ q-1 $ seconds of the track.

Tell Lesha, for how many times he will start the song, including the very first start.

## 说明/提示

In the first test, the song is played twice faster than it is downloaded, which means that during four first seconds Lesha reaches the moment that has not been downloaded, and starts the song again. After another two seconds, the song is downloaded completely, and thus, Lesha starts the song twice.

In the second test, the song is almost downloaded, and Lesha will start it only once.

In the third sample test the download finishes and Lesha finishes listening at the same moment. Note that song isn't restarted in this case.

## 样例 #1

### 输入

```
5 2 2
```

### 输出

```
2
```

## 样例 #2

### 输入

```
5 4 7
```

### 输出

```
1
```

## 样例 #3

### 输入

```
6 2 3
```

### 输出

```
1
```

# 题解

## 作者：封禁用户 (赞：1)

题目传送门：[CF569A Music](https://www.luogu.com.cn/problem/CF569A)

**题目翻译：** Little Lesha喜欢听歌，**且喜欢边下载变听** 。Lesha最喜欢听的歌需要下载，这首歌的播放时间是$T$秒。Lesha先下载了$S$秒，每$q$秒可以下载$q-1$秒的歌，当将要播放的还没下载，则会从头开始听，问：当下载完这首歌是，一共从头开始了多少次？

**题解：** 我们假设到没有下载的时间为$a$秒，则可得$(q-1)\div q\times a+S=a$，解出$a=q\times S$后，代码就很容易了。

$Code:$

```pascal
var T,S,q,n:longint;
begin
  read(T,S,q);
  while S<T do
  begin
    S:=S*q;
    inc(n);
  end;
  write(n);
end.
```


---

## 作者：qifan_maker (赞：0)

### 题目链接
[洛谷](https://www.luogu.com.cn/problem/CF569A)

[Codeforces](https://codeforces.com/problemset/problem/569/A)
### 题目解法
已知 $q$ 秒下载 $q-1$ KB，则每秒下载 $\frac{q-1}{q}$ KB。

那么 $time = s+\frac{q-1}{q}$，也就是 $time = sq$。
### AC Code
```cpp
#include<bits/stdc++.h>
using namespace std;
int main(){
	int t,s,q;
	cin >> t >> s >> q;
   int cnt=0;
	while (s<t){
		s *= q;
		cnt++;
	}
	cout << cnt;
}
```

---

## 作者：zjr0330 (赞：0)

中文题面看别的题解。。。

这道题很简单，我们知道每 $q$ 秒可以下载 $q-1$ KB，那么不难得出，每秒能下载 $\frac{q-1}{q}$ KB 的音乐，我们在设一个 $m$ 表示音乐的时间，就可以得到方程 $\frac{q-1}{q}+s=m$。

解得 $m=sq$。

于是(~~复~~)简(~~杂~~)单的代码就得出来啦：

```cpp
#include<bits/stdc++.h>
using namespace std;
int main(){
	int t,s,q,ans=0;
	for(cin>>t>>s>>q;s<t;){
		s=s*q;
		ans++;
	}
	cout<<ans<<endl;
	return 0;
}
```


---

## 作者：MYFJWHR (赞：0)

主要问题是没有翻译。

题解
-------------

略过题意。

设还有 $x$ 秒这首歌播放到结尾，因为每 $q$ 秒可以下载 $q-1$ 的曲子，所以一秒就可以下出 $q-1 \over q$ KB的文件。

**所以可以得出方程**：$ \dfrac {q-1}{q} +s=y$, 显然，$y=s\times q$。

所以，代码就：

```c
#include<bits/stdc++.h>
using namespace std;
int t,s,q,ans;
int main(){
	scanf("%d%d%d",&t,&s,&q);
	while(s<t){
		s*=q;
		ans++;
	}
	printf("%d",ans);
}
```

完结撒花，AC大吉。


---

## 作者：Neilchenyinuo (赞：0)

## 解题思路

我们可以定义一个 $t$ 为总时间。

已知每 $q$ 秒可以下载 $(q-1)$ KB，每秒就能下载 $(q-1)/q$ KB。

列出方程：$(q-1)/q+s=t$，解出 $t=sq$。

## 上代码~~

```cpp
#include<bits/stdc++.h>//万能头 
using namespace std;
int s,t,q,cnt;
int main()
{
    cin>>t>>s>>q;//总时间 已下载的量  每次下载的时间 
    while(t>s) 
    {
        s*=q;//根据方程  t=sq  
        cnt++;//统计次数 
    }
    cout<<cnt;
    return 0;//好习惯 
} 
```


---

## 作者：_VEGETABLE_OIer_xlc (赞：0)

[题目传送门](https://www.luogu.com.cn/problem/CF569A)

## 题意（简短版）

一首歌的播放时间为 $T$ 秒，已经下载了 $S$ 秒，每 $q$ 秒可以下载 $q - 1$ 秒的音乐，每当下一秒要播放的音乐没被下载时就从 $0$ 秒开始听，问会有几次重新？

首先，题目说 $q$ 秒可以下载 $q - 1$ 秒的音乐，则 $1$ 秒可以下载 $\frac{q - 1}{q}$ 秒的音乐。

设 $y$ 秒后播放到音乐的结尾，则有 $\frac{q - 1}{q}$ $ + $ $ S $ $ = $ $ y $。

解出 $y$ $=$ $sq$。

代码就呼之欲出了！

```cpp
#include<bits/stdc++.h>
using namespace std;
int main(){
	int t,s,q;
	cin>>t>>s>>q;//按题目要求输入
	int ans=0;
	while(s<t)
	{
		s=s*q;
		ans++;
	}
	cout<<ans;
	return 0;
}

```



---

## 作者：JZH123 (赞：0)

# 解题思路
设到 $y$ 秒时听到已下载部分的尾端。

$q$ 秒下载 $(q - 1) \textrm{kb}$ ，即         : $1$ 秒时下载 $[(q - 1) / q] \textrm{kb}$。

列方程式： $(q - 1) / q + s = y$

最终结果为 $y = sq$。

# 上代码——
```
#include<bits/stdc++.h>
using namespace std;
int T, s, q, cnt;
int main()
{
    scanf ("%d%d%d", &T, &s, &q);
    while (s < T)
    {
        s *= q;
		cnt ++;
	} 
    printf ("%d", cnt);
    return 0;
}
```

---

