# [ARC006A] 宝くじ

## 题目描述

[problemUrl]: https://atcoder.jp/contests/arc006/tasks/arc006_1

 高橋君は夏の宝くじをこっそり買っていました。今日はその宝くじの当選発表日です。購入者は、$ 0 $ から $ 9 $ までの $ 10 $ 個の数字から重複せずに $ 6 $ つの数字を選び購入します。発表日には $ 6 $ つの本数字と $ 1 $ つのボーナス数字が発表され、購入した宝くじとその数字がいくつ一致しているかで以下のように当選の等級が決まります。

- $ 1 $ 等 : $ 6 $ つ数字が一致
- $ 2 $ 等 : $ 5 $ つ数字が一致し、残りの $ 1 $ つの数字がボーナス数字と一致
- $ 3 $ 等 : $ 5 $ つ数字が一致
- $ 4 $ 等 : $ 4 $ つ数字が一致
- $ 5 $ 等 : $ 3 $ つ数字が一致
 
 上記のどれにも当てはまらない場合ははずれになります。 また、複数の等級を満たす場合は上位の等級（数字が小さい等級）が適用されます。  
  
 高橋君が購入した宝くじの等級を求めなさい。 なお、与えられる当選番号とボーナス数字の $ 7 $ つの数字は互いに異なります。 入力は以下の形式で標準入力から与えられる。 > $ E_0 $$ E_1 $$ E_2 $$ E_3 $$ E_4 $$ E_5 $ $ B $ $ L_0 $$ L_1 $$ L_2 $$ L_3 $$ L_4 $$ L_5 $

- 入力は $ 3 $ 行ある。
- $ 1 $ 行目には、当選番号を表す $ 6 $ つの整数 $ E_i(0≦i≦5, $ $ 0≦E_i≦9) $ が与えられる。
- $ E_i $ は昇順に並んでいる。

- $ 2 $ 行目には、ボーナス数字を表す整数 $ B(0≦B≦9) $ が与えられる。
- $ 3 $ 行目には、高橋君が購入した宝くじの $ 6 $ つの数字を表す整数 $ L_j(0≦j≦5, $ $ 0≦L_j≦9) $ が与えられる。
- $ L_i $ は昇順に並んでいる。
- $ L_i $ の $ 6 $ つの数字は互いに異なります。

- $ E_i $ と $ B $ を合わせた $ 7 $ つの数字は互いに異なります。
 
 高橋君が購入した宝くじの等級数 ($ 1 $ 等の場合は `1`、$ 2 $ 等の場合は `2`、のように) を標準出力に $ 1 $ 行で出力せよ。  
 また、はずれの場合は `0` を出力せよ。  
 なお、最後には改行を出力せよ。 ```

1 2 3 4 5 6
7
1 2 3 4 5 6
```

 ```

1
```

- $ 6 $ つの数字全てが当選番号と購入宝くじとで一致しているので、$ 1 $ 等にになります。
 
```

0 1 3 5 7 9
4
0 2 4 6 8 9
```

 ```

0
```

- 一致している数字が $ 0 $ と $ 9 $ の $ 2 $ つのみなので、当選の条件を満たさず、はずれです。
 
```

0 2 6 7 8 9
4
0 5 6 7 8 9
```

 ```

3
```

- $ 0,\ 6,\ 7,\ 8,\ 9 $ の $ 5 $ つが一致していますが、ボーナス数字の $ 4 $ は購入した宝くじの数字の中にないので $ 3 $ 等になります。
 
```

1 3 5 6 7 8
9
3 5 6 7 8 9
```

 ```

2
```

- $ 3,\ 5,\ 6,\ 7,\ 8 $ の $ 5 $ つが一致しており、ボーナス数字の $ 9 $ も購入した宝くじの数字の中にあるので $ 2 $ 等になります。
 
```

0 1 3 4 5 7
8
2 3 5 7 8 9
```

 ```

5
```

- $ 3,\ 5,\ 7 $ の $ 3 $ つの数字が一致しているので $ 5 $ 等になります。

# 题解

## 作者：绿绵羊 (赞：7)

# 为神马各位大佬都要写那么复杂······
## 明明用数组就能AC呀~
每个中奖号码x为-1，选择数x为1，以此类推，则a[x]如果为正数，那么这一位出错，如果为0，那么这一位正确。最后根据题目要求输出，不就可以了吗？
```cpp
#include <bits/stdc++.h>
using namespace std;
int main()
{
	int x, i, a[10], h, t=0;
	for (i=0; i<=9; i++) a[i]=0;
	for (i=1; i<=6; i++)
	{
		cin >> x;
		a[x]--;
	}
	cin >> h;
	for (i=1; i<=6; i++)
	{
		cin >> x;
		a[x]++;
	}
	for (i=0; i<=9; i++)
		if (a[i]>0) t+=a[i];
	if (t==0) cout << 1 << endl;
	else if (t==2) cout << 4 << endl;
	else if (t==3) cout << 5 << endl;
	else if (t>=4) cout << 0 << endl;
	else
	{
		for (i=0; i<=9; i++)
			if (a[i]>0)
			{
				if (i==h)
				{
					cout << 2 << endl;
					return 0;
				}
				else
				{
					cout << 3 << endl;
					return 0;
				}
			}
	}
	return 0;
}
```

---

## 作者：PC_DOS (赞：3)

本题目为一道模拟题，大致的思路是:

先判断购买的编号之中有多少个和中奖序列重合，如果恰好有5个重合，那么判断那唯一一个不同的数字是不是附加号，最后输出中奖等级。

代码:
```
#include <iostream>
#include <algorithm>
using namespace std; //头文件和命名空间
int main(){
    ios::sync_with_stdio(false); //输入输出加速
    bool IsSpecial = false; //是不是二等奖，默认为假
    int arrPrize[6], iNumPrize, arrBuy[6], nCount = 0; //arrPrize-中奖序列；iNumPrize-附加中奖编号；arrBuy-购买的奖券编号；nCount-重合的数的个数
    register int i; //循环计数器
    for (i = 0; i <= 5; ++i){ //读入中奖序列
        cin >> arrPrize[i];
    }
    cin >> iNumPrize; //读入附加号
    for (i = 0; i <= 5; ++i){ //读入购买序列
        cin >> arrBuy[i]; //读入一个数
        if (count(arrPrize, arrPrize + 6, arrBuy[i])){ //如果中奖序列中存在这个数
            ++nCount; //个数增加
        }
    }
    if (nCount == 5){ //5个相同的时候特判
        for (i = 0; i <= 5; ++i){ //查找不同的数字
            if (count(arrPrize, arrPrize + 6, arrBuy[i]) == 0 && arrBuy[i] == iNumPrize){ //如果是附加号
                IsSpecial = true; //二等奖确定
            }
        }
    }
    if (nCount == 6) //6个数都相同
        cout << 1 << endl; //一等奖
    else if (nCount == 5) //如果5个数相同
        if (IsSpecial) //判断是不是二等奖
            cout << 2 << endl; //二等奖
        else
            cout << 3 << endl; //三等奖
    else if (nCount == 4) //如果4个数相同
        cout << 4 << endl; //四等奖
    else if (nCount == 3) //如果3个数相同
        cout << 5 << endl; //五等奖
    else //否则
        cout << 0 << endl; //没有QwQ
    return 0; //结束
}
```

---

## 作者：shcweb (赞：1)

这道题本蒟蒻用STL做的

用了<algorithm>里的set_intersection(取两集合交集)和set_difference(取两集合差集)函数
  
这两个函数的括号内均为五个参数，分别为
- 第一个集合的头尾
- 第二个集合的头尾
- 最后一个参数这里用 inserter(s, s.begin())，即把结果插入到集合s中去
  
代码如下
  
```cpp
#include<bits/stdc++.h>          //万能头文件
using namespace std;

int main()
{
    set<int> a, b, s;            //a为中奖号码，b为选择的号码
    int c;                       //奖励号码
    for(int i = 0; i < 6; i++)   //把中奖号码存入集合a
    {
        int num;
        cin >> num;
        a.insert(num);
    }
    cin >> c;                    //把奖励号码存入c
    for(int i = 0; i < 6; i++)   //把选择的号码存入集合b
    {
        int num;
        cin >> num;
        b.insert(num);
    }
    //取a与b的交集存入集合s
    set_intersection(a.begin(), a.end(), b.begin(), b.end(), inserter(s, s.begin()));
    if(s.size() == 6)        //s中有6个元素,即6个数全部相同,以下同理
        cout << 1 << endl;
    else if(s.size() == 3)   //3个数相同
        cout << 5 << endl;
    else if(s.size() == 4)   //四个数相同
        cout << 4 << endl;
    else if(s.size() == 5)   //五个数相同
    {
        set<int>ss;
        //取b与s的差集存入集合ss,ss中应有一个元素即唯一不同的数字
        set_difference(b.begin(), b.end(), s.begin(), s.end(), inserter(ss, ss.begin()));
        if(ss.count(c) == 0)     //如果奖励数字在集合ss中
            cout << 3 << endl;
        else
            cout << 2 << endl;
    }
    else
        cout << 0 << endl;       //如果不符合以上全部情况
    return 0;
}
```

---

## 作者：我是蒟弱 (赞：0)

### 思路：读入彩票号码，标记彩票号码，判断中了几个，最后判断几等奖

那么我们上代码看一下，具体看注释，我写的很详细 ~~（自夸）~~：
```cpp
#include<iostream>
#include<cstdio>
#include<algorithm>
#include<cmath>
#include<cstring>
using namespace std;
int main(){
	int a,b,c,d,e,f,extra,za,zb,zc,zd,ze,zf,t[10]={},ans=0;
	//a,b,c,d,e,f是彩票号码
	//extra是额外的奖励号码
	//za,zb,zc,zd,ze,zf是选择的号码
	//t[i]表示数字i是否是彩票，是1就是彩票，是0就不是彩票
	//ans统计中奖个数 
	cin>>a>>b>>c>>d>>e>>f>>extra;//输入彩票 
	t[a]=t[b]=t[c]=t[d]=t[e]=t[f]=1;//标记彩票 
	cin>>za>>zb>>zc>>zd>>ze>>zf;//输入选择的 
	if(t[za]) ans++;
	if(t[zb]) ans++;
	if(t[zc]) ans++;
	if(t[zd]) ans++;
	if(t[ze]) ans++;
	if(t[zf]) ans++;//一个一个判断是否中奖 
	if(ans==6) cout<<1;//如果全中奖，1等奖 
	else if(ans==5)//中了5个 
		if(za==extra||zb==extra||zc==extra||zd==extra||ze==extra||zf==extra) cout<<2;//另外一个是奖励号码，2等奖 
		else cout<<3; //如果不是，那就是3等奖 
	else if(ans==4) cout<<4;//如果中了4个，4等奖 
	else if(ans==3) cout<<5;//如果中了3个，5等奖 
	else cout<<0;//如果其他条件，没中奖 
	cout<<endl;//AT的题不输出换行，会"听取WA声一片" 
	return 0;
}

```


---

## 作者：wzyx (赞：0)

~~一道模拟水题~~

有几个要注意的

1.输出最后一定换行

2.若不得奖，输出0

上代码

```
#include<bits/stdc++.h>
using namespace std;
int main()
{
    int al[7],k,a,b=0,c=0,i,j,m;
    for(i=1;i<=6;i++)
    {
        cin>>al[i];
    }
    cin>>a;
    for(i=1;i<=6;i++)
    {
        m=0;
        cin>>k;
        for(j=1;j<=6;j++)
        {
            if(k==al[j])
            {
                b++;
                al[j]=-1;
                m=1;
                break;
            }
        }
        if(m==1)
        {
            continue;
        }
        if(k==a)
        {
            c++;
        }
    }
    if(b==6)
    {
        cout<<1<<endl;
        return 0;
    }
    if((b==5)&&(c==1))
    {
        cout<<2<<endl;
        return 0;
    }
    if(b==5)
    {
        cout<<3<<endl;
        return 0;
    }
    if(b==4)
    {
        cout<<4<<endl;
        return 0;
    }
    if(b==3)
    {
        cout<<5<<endl;
        return 0;
    }
    cout<<0<<endl;
    return 0;
}
```




---

## 作者：不到前10不改名 (赞：0)

再一次来发at的题解
```
#include<stdio.h>
int srx[7],mzy,sry,lhy,zjq,i,j,//233防伪标识
int main()
{
    for(i=1;i<=6;i++)
    scanf("%d",&srx[i]);
    scanf("%d",&sry);
    for(i=1;i<=6;i++)
    {lgx=0;//这里是一个2次判断，用来判断2等的奖励数
    scanf("%d",&mzy);
    for(j=1;j<=6;j++)
    {if(mzy==srx[j])
    {lhy++;
    srx[j]=-1;
    lgx=1;
    break;}}
    if(lgx==1)
    continue;
    if(mzy==sry)
    zjq=1;}
    if(lhy==6)//if else判断就不说了！
    printf("1\n");
    else if(lhy==5&&zjq==1)
    printf("2\n");
    else if(lhy==5)
    printf("3\n");
    else if(lhy==4)
    printf("4\n");
    else if(lhy==3)
    printf("5\n");
    else
    printf("0\n");
    return 0;
}
```

---

## 作者：loi_hjh (赞：0)

## 请忽略那些奇奇怪怪用来好看的头文件

五个数相同且不同的数与奖励号码相同：2等奖；

五个数相同：3等奖

这是个坑

# 注：做AT系列的题一定要在答案后输出换行，不然你会WA的很惨

```cpp
#include<map>
#include<list>
#include<cmath>
#include<cstdio>
#include<cstring>
#include<iostream>
#include<algorithm>
using namespace std;
bool b[8];//在中5个数时用 
int a[7],c[7],n,ans;//a是我的号码，c是标准号码，n是奖励号码，ans是中奖个数 
int main(){
	for(int i=1;i<=6;i++)//读入标准号码
		scanf("%d",&c[i]);
	scanf("%d",&n);//读入奖励号码 
	for(int i=1;i<=6;i++){
		scanf("%d",&a[i]);//每读入一个我的号码都进行一次for看看中没中（不考虑顺序） 
		for(int j=1;j<=6;j++)
			if(a[i]==c[j]){
				b[i]=true;//这个号码中了，b变成true，在ans=5时用到 
				ans++;
			}
	}
	//接下来是看中了几个，除了5不解释 
	if(ans==6) printf("1");
	if(ans==5){
		for(int i=1;i<=6;i++)
			if((!b[i])&&(a[i]==n)){//这个号没中才参与判定中没中奖励号码 
				b[7]=true;//b[7]只是当个变量，与我的号码没关系 
				printf("2");
				break;
			}
		if(!b[7]) printf("3");
	}
	if(ans==4) printf("4");
	if(ans==3) printf("5");
	if(ans<3) printf("0");
	putchar('\n'); 
	return ~~(0-0);
}


```


---

