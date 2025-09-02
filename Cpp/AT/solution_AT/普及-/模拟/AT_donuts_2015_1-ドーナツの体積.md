# ドーナツの体積

## 题目描述

[problemUrl]: https://atcoder.jp/contests/donuts-2015/tasks/donuts_2015_1

問題設定に不備がありました．また，R&gt;Dであるようなテストケースが存在していました．R＜Dという制約を問題に付け加え，テストケースの修正作業を行います．作業が完了次第リジャッジを行います．(19:14)

リジャッジが完了しました．(19:21)

ドーナツの体積を計算してみましょう。

平面図形をある直線を軸に回転させてできる立体の体積は、

- 「平面図形の面積」$ \times $「平面図形の重心が描く円の周長」

という式で求めることができます。

半径 $ R $ の円を、円の中心からの距離が $ D $ である直線を軸に回転させてできるドーナツ型の立体の体積を計算してください。

 ![](https://cdn.luogu.com.cn/upload/vjudge_pic/AT_donuts_2015_1/eeff4bda71c040930852a2e4a36e378f8d49d232.png)![](https://cdn.luogu.com.cn/upload/vjudge_pic/AT_donuts_2015_1/78ff6ecb28a3aa650ce7bb2df4d3ea4e7275c051.png)

## 说明/提示

### Sample Explanation 1

半径が $ 3 $ の円を、円の中心からの距離が $ 5 $ である直線を軸に回転させてできる立体の体積を出力すれば良いです。 「平面図形の面積」は $ 3^2\ \times\ π $ で、「平面図形の重心が描く円の周長」は $ 5\ \times\ 2\ \times\ π $ なので、体積は $ 90\ \times\ π^2 $ となります。 円の重心は中心であることに注意してください。

## 样例 #1

### 输入

```
3 5```

### 输出

```
888.264396```

## 样例 #2

### 输入

```
46 96```

### 输出

```
4009743.9192393753```

# 题解

## 作者：RioBlu (赞：1)

本题是一个我没有翻译看最后一个说明知道题意的

翻译：输入R和D，输出$R^2*D*2*π^2$，误差不超过$10^{-2}$
```
#include<bits/stdc++.h>
using namespace std;
double a,b;
int main()
{
	cin>>a>>b;
	printf("%.10lf\n",a*a*b*2*3.1415926535*3.1415926535);
}
```

---

## 作者：CZQ_King (赞：0)


本题题目非常水，是求出圆环的体积。
#### 蒟蒻在这里提出另一种解法

------------

这里有$2$个体积公式：
![](https://cdn.luogu.com.cn/upload/pic/32278.png)
- $2*\pi^2*D*R^2$
- $\frac{\pi^2*(b+a)*(b-a)^2}{4}$


------------

由于第一种方法被@RioBlu 大佬~~(本人师父~~所用，所以使用第二种方法。
```cpp
#include<bits/stdc++.h>//头文件
using namespace std;
double R,D,a,b,V,p=3.1415926535;//各种变量
int main(){
	cin>>R>>D;
	a=D-R;
	b=D+R;//把a和b求出来
	V=p*p*(b+a)*(b-a)*(b-a)/4;//套入公式
	cout<<fixed<<setprecision(10)<<V<<endl;//输出
	return 0;//结束
}
```

---

