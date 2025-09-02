# Mike and Cellphone

## 题目描述

迈克在海滩游泳时不小心将手机放入水中。他买了一个带有老式键盘的手机。键盘只有十个数字大小的键，位于以下方式：

| 1 | 2 | 3 |
| -----------: | -----------: | -----------: |
| 4 | 5 | 6 |
| 7 | 8 | 9 |
|   | 0 |   |   |
联系人与他的旧手机一起消失了，他现在只能记住他的手指在他输入一些数字时的移动方式。人们可以将手指动作视为连接按下按键的一系列动作。例如，数字“586”的手指移动动作与数字“253”的手指移动动作相同。
Mike通过他的“手指记忆”输入了一个数字并开始调用它，所以他现在担心，有没有其他数字，有相同的手指动作？

## 样例 #1

### 输入

```
3
586
```

### 输出

```
NO
```

## 样例 #2

### 输入

```
2
09
```

### 输出

```
NO
```

## 样例 #3

### 输入

```
9
123456789
```

### 输出

```
YES
```

## 样例 #4

### 输入

```
3
911
```

### 输出

```
YES
```

# 题解

## 作者：亦枫 (赞：3)

## Solution

题意：给你一个在老式键盘上的按键顺序，问你存不存在和这一组按键的按法相对位置顺序的按键按法。

首先，我们在得到有 $ 1 $，$ 2 $，$ 3 $ 这三个按键的时候是不能向上移动的。

同理，我们可以得到：

有 $ 1 $，$ 4 $，$ 7 $，$ 0 $ 这几个按键的时候不能向左移动。

有 $ 3 $，$ 6 $，$ 9 $，$ 0 $ 这几个按键的时候不能向右移动。

有 $ 7 $，$ 9 $，$ 0 $ 这几个按键的时候不能向下移动。

所以，这题就简单的枚举一遍每个字符，进行判断即可。

关键部分如下：

```cpp
for(int i=0;i<n;i++){
	if(s[i]=='0'||s[i]=='7'||s[i]=='9')down=false;//对能否下移进行判断
	if(s[i]=='1'||s[i]=='7'||s[i]=='4'||s[i]=='0')le=false;//对能否左移进行判断
	if(s[i]=='1'||s[i]=='2'||s[i]=='3')up=false;//对能否上移进行判断
	if(s[i]=='3'||s[i]=='6'||s[i]=='9'||s[i]=='0')ri=false;//对能否右移进行判断
}
```


---

## 作者：long_long (赞：2)

# 题目大意：

 输入的第一行包含唯一的整数n（1<=N<=9）表示Mike输入的电话号码中的位数。第二行由1到9组成的n个字符的字符串。 如果没有其他电话号码具有相同的手指移动，则输出“YES”，否则输出“NO”（不带引号）。
 
 
# 思路：

![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF689A/0342f4147f163e7abcc57c3f34c170ac4ad52a2c.png)

这是一个老人机键盘，要判断一个长度为n的号码是否有重复的手法。

举个栗子：

这是号码“586”的手法
![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF689A/1ee471f119d0342dde68609c8abcbc49afcbf489.png)

这是号码“253”的手法
![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF689A/030b9a0e4d0e91a9966bf07663da14ee536572b7.png)

他们两个号码的手法都是往下，再往右上方。因此这一组输出“NO”。

### 所以这道题只需要判断这个号码归于哪个手法就得了。

# 康康代码：

```
#include<iostream>
#include<string>
using namespace std;
bool lef=true,rit=true,up=true,dow=true;//定上下左右的布尔，初始化为真
int main(){
    int n;//n表示长度
    string m;//m表示号码
    cin>>n>>m;//输入
    for(int l=0;l<n;l++){//循环
        if(m[l]=='0'){lef=false;rit=false;dow=false;}//如果这个号码有0，那么下左右就别想了（可以观察一下第一张图）
        if(m[l]=='9'||m[l]=='3'||m[l]=='6') rit=false;//如果这个号码有9，3，6，右就别想了（见图
        if(m[l]=='4'||m[l]=='7'||m[l]=='1')lef=false;//如果这个号码有4，7，1，左就别想了（见图）
        if(m[l]=='1'||m[l]=='2'||m[l]=='3')up=false;//如果这个号码有1，2，3，上就别想了（见图
        if(m[l]=='9'||m[l]=='7') dow=false;//如果这个号码有9，7，下就别想了（见图）
    }
    if(!lef||!rit||!up||!dow){ //最后判断哪个是false
        cout<<"YES"<<endl;//输出
        return 0;//结束程序
    } 
    cout<<"NO"<<endl;//输出
    return 0;//华丽结束
}
```



---

## 作者：世末OIer (赞：2)

通过键盘我们可以得知，如果在123或709或147或359或0中这些组合中有一个数被用到了就是可以的。直接模拟就行了

```cpp
#include<bits/stdc++.h>
using namespace std;
int n;
string s;
map<int,int>b;
int main(){
	cin>>n>>s;
	for (int i=0;i<n;i++) b[s[i]-'0']++;
	if ((b[1] or b[2] or b[3]) and (b[7] or b[0] or b[9])and(((b[1] or b[4] or b[7])and(b[3] or b[6] or b[9])) or b[0])) cout<<"YES";
	else cout<<"NO";
}
```

---

## 作者：Noby_Glds (赞：0)

做完后看了一下题解，发现大佬们的做法如出一辙啊。

介绍一种新的做法：坐标系！

我们把这个老年机粘在坐标系上。

![](https://cdn.luogu.com.cn/upload/image_hosting/eq9hjf3i.png?x-oss-process=image/resize,m_lfit,h_170,w_225)

这样每个按键都有它的坐标了。

按键的坐标为可选坐标，其他的为不可选坐标，可选坐标在二维数组 $a$ 内标记为 $1$。

用二维数组 $b$ 记录按键的坐标。

接着枚举所有按键，如果此按键（以下称为目标按键）不为 Mike 所按的第一个按键（以下称为原按键），则由它引出手指动作。

**复杂**的部分开始了。

用 $p1$ 存储从原按键到目标按键需左移多少格，如果为负数则为右移，$p2$ 存储从原按键到目标按键需下移多少格，如果为负数则为上移。

接着把原按键后面要按的按键的横，纵坐标分别加上 $p1$ 和 $p2$。然后判断该坐标是否为合法坐标。如果该坐标为合法坐标，计数器 $p$ 加一。

如果最终 $p$ 等于 $n$，就说明有其他的手指移动，输出 $\texttt{NO}$ 然后结束程序。

如果坚持到了最后，输出 $\texttt{YES}$。

### 代码：
```cpp
#include<bits/stdc++.h>
using namespace std;
int a[10][10],b[10][3],p=1;
char q[11];
int main(){
    int n;
    cin>>n;
    a[1][4]=a[1][3]=a[1][2]=a[2][4]=a[2][3]=a[2][2]=a[2][1]=a[3][4]=a[3][3]=a[3][2]=1;
    b[0][1]=b[8][1]=b[5][1]=b[2][1]=2;
    b[7][1]=b[4][1]=b[1][1]=1;
    b[9][1]=b[6][1]=b[3][1]=3;
    b[1][2]=b[2][2]=b[3][2]=4;
    b[4][2]=b[5][2]=b[6][2]=3;
    b[7][2]=b[8][2]=b[9][2]=2;
    b[0][2]=1;    //一堆初始化。
    for(int i=0;i<=n-1;i++) cin>>q[i];
    for(int i=0;i<=9;i++){
        if(i!=q[0]-'0'){
            int p1,p2;
            p1=b[q[0]-'0'][1]-b[i][1];
            p2=b[q[0]-'0'][2]-b[i][2];
            for(int j=1;j<strlen(q);j++){
                if(a[b[q[j]-'0'][1]-p1][b[q[j]-'0'][2]-p2]==1) p++;
            }
            if(p==strlen(q)){
                cout<<"NO";
                return 0;
            }
        }
        p=1;   //注意，p要初始为1。
    }
    cout<<"YES";
    return 0;
}
```
最优解第二，虽然复杂，但不妨碍它好用啊。

---

## 作者：Cambridge (赞：0)


蒟蒻又来发题解了！

### 思路

这是一个老人机键盘。

![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF689A/0342f4147f163e7abcc57c3f34c170ac4ad52a2c.png)

我们要判断的是输入的这个号码的手法跟输入其他等长度号码的手法是否有重复。

举个例子：

![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF689A/1ee471f119d0342dde68609c8abcbc49afcbf489.png)

上方是输入“586”的手法，我们会发现，他输入的手法跟“253”是一样的：

![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF689A/030b9a0e4d0e91a9966bf07663da14ee536572b7.png)

当然，它跟“475”的手法也是一样的，这里就不画图了。

那我们就可以对输入的号码中的边界数字进行处理了。一共有8个数字为边界数字，处理如下：

> * 当前数字为0时，它的下、左、右方向不可移动。
> * 当前数字为1时，它的上、左方向不可移动。
> * 当前数字为2时，它的上方向不可移动。
> * 当前数字为3时，它的上、右方向不可移动。
> * 当前数字为4时，它的左方向不可移动。
> * 当前数字为6时，它的右方向不可移动。
> * 当前数字为7时，它的下、左方向不可移动。
> * 当前数字为9时，它的下、右方向不可移动。

最后我们再来看，如果当前号码手法上下左右都不可移动，那么这个号码手法就是独一无二的。

思路如上，代码如下：

```cpp
#include<iostream>
#include<cstring>
#include<cstdio>
#include<cmath>
#include<vector>
#include<fstream>
#include<algorithm>//文件头不解释
using namespace std;
int n;
bool a,b,c,d;//a是上边，b是下边，c是左边，d是右边
string st;
//定义变量
int main()
{
	cin>>n>>st;
	for(int i=0; i<n; i++)
   	{
		if(st[i]=='0')b=1,c=1,d=1;
      	if(st[i]=='1')a=1,c=1;
      	if(st[i]=='2')a=1;
      	if(st[i]=='3')a=1,d=1;
      	if(st[i]=='4')c=1;
      	if(st[i]=='7')b=1,c=1;
      	if(st[i]=='6')d=1;
      	if(st[i]=='9')b=1,d=1;
      	//解释看上方思路
	}
	if(a&&b&&c&&d)cout<<"YES";//如果四个方向都是唯一的
	else cout<<"NO";//如果四个方向不唯一
	return 0;
}
```

好了，1本蒟蒻就讲到这里，希望对读者有所帮助。

---

## 作者：Accteped (赞：0)

## 思路
对四周进行判断能不能出现第二种情况，如果四周都不行，那就判定没有其他电话号码具有相同的手指移动，就输出YES,反之输出NO

![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF689A/0342f4147f163e7abcc57c3f34c170ac4ad52a2c.png)
这是电话键盘，只需对输入的电话号码的各个数字进行模拟即可

![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF689A/1ee471f119d0342dde68609c8abcbc49afcbf489.png)
如图，输入的样例为586，首先遍历5，它的上方可以走，左边也可以走，下面和左边都可以……所以判定为NO

## CODE
```cpp
#include<bits/stdc++.h>
using namespace std;
bool up,down,lft,rgt;
int main(){
	int n;
	cin>>n;
	string s;
	cin>>s;
	for(int i=0;i<n;++i){
		if(s[i]=='0')down=1,lft=1,rgt=1;
		if(s[i]=='1'||s[i]=='2'||s[i]=='3')up=1;
		if(s[i]=='1'||s[i]=='4'||s[i]=='7')lft=1;
		if(s[i]=='3'||s[i]=='6'||s[i]=='9')rgt=1;
		if(s[i]=='7'||s[i]=='9')down=1;
	}
	if(up&&down&&lft&&rgt)cout<<"YES";
	else cout<<"NO";
	return 0;
}
```


---

## 作者：FuriousC (赞：0)

[题目传送门](https://www.luogu.com.cn/problem/CF689A)

# 思路

**模拟**

判断一下给出的输入方法中的数字向哪里走会碰壁，只要上下左右$4$个方向全部碰壁，那么这个方法就是唯一的

大体思路就是一个一个数判断

$eg$：如果输入的字符串里有$0$的话，那么肯定是不能往下、右或左走的，因为向下或左或右走会碰壁

详细判断见代码注释

# 废话不多说，上代码：

```cpp
#include<bits/stdc++.h>//懒人专用头文件
using namespace std;
typedef long long ll;
bool shang,xia,zuo,you;//上下左右显而易见 
int n;
string a;//n,a见题面 
int main(){
   cin>>n>>a;//输入 
   for(int i=0;i<n;i++){
        if(a[i]=='0'){ 
            xia=1;
            zuo=1;
            you=1;//有0则不能往下或左或右走 
        }else if(a[i]=='1'){
            shang=1;
            zuo=1;//有1则不能往上或左走 
        }else if(a[i]=='2'){
            shang=1;//有2则不能往上走 
        }else if(a[i]=='3'){
            shang=1;
            you=1;//有3则不能往上或右走
        }else if(a[i]=='4'){
            zuo=1;//有4则不能往左走
        }else if(a[i]=='6'){
            you=1;//有6则不能往右走
        }else if(a[i]=='7'){
            zuo=1;
            xia=1;//有7则不能往左或下走
        }else if(a[i]=='9'){
            you=1;
            xia=1;//有9则不能往右或下走
        }
   }//因为5和8上下左右4个方向都能走，所以不做判断
   if(shang==1&&xia==1&&zuo==1&&you==1){
        cout<<"YES"<<endl;//表示没有其他相同的走法 
   }else{
        cout<<"NO"<<endl;//有其他相同的走法 
   }
   return 0;//好习惯 
}
```

代码看完了，你学废了吗？

---

## 作者：TLMPEX (赞：0)

思路：这道题用char读入，每读入一个数字就查找它的坐标，查找完了后用一个双层循环枚举，第一层枚举方向，第二层枚举1至n个数字，如果每一个数字都能向同一个移动，则其他电话号码具有相同的手指移动，反之则没有。

```c
#include<bits/stdc++.h>
using namespace std;
int k[10],vis[6][5];
int a[4]={-1,0,0,1},b[4]={0,-1,1,0};//四个方向
struct node{
	int x,y;
}keys[1001];
void csh(){//初始化,把10个键都置0，其他置-1
	int i,j,o=0;
	memset(vis,-1,sizeof(vis));
	for(i=1;i<=3;i++)
		for(j=1;j<=3;j++){
			o++;
			vis[i][j]=o;
		}
	vis[4][2]=0;
}
void fd(int o,int r){//查找这个数字在哪一行那一列
	for(int i=1;i<=4;i++)
		for(int j=1;j<=3;j++)
			if(vis[i][j]==r-'0'){//如果找到了就记录下来
				keys[o].x=i;
				keys[o].y=j;
			}
}
int main(){
	int n,i,j,t=0;
	char r;
	cin>>n;
	csh();
	for(i=1;i<=n;i++){
		cin>>r;
		fd(i,r);
	}
	for(i=0;i<4;i++){
		for(j=1;j<=n;j++){
			node t=keys[j];
			if(vis[t.x+a[i]][t.y+b[i]]==-1)//如果下一个位置不在键盘里了，说明这n个数字中一个不能向此方向移动，则break
				break;
		}
		if(j==n+1)t=1;//如果是自然结束，那就标记t为1,
	}
	if(t)cout<<"NO";//如果t为1，输出NO
	else cout<<"YES";
}
```


---

