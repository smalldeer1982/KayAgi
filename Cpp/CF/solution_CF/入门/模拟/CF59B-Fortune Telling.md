# Fortune Telling

## 题目描述

玛丽娜喜欢萨沙。但她一直在想萨沙是否爱她。当然，知道的最好方法就是去占卜。占卜的方法有很多，但是玛丽娜选择了最简单的一个方法。她拿起一只或几只甘菊，一个接一个地掰下花瓣。在每个花瓣之后，她说出“爱”或“不爱”，第一个掰的花瓣后先说“爱”。有 $n$ 朵甘菊在田间生长，它们的花瓣数等于$a_1$，$a_2$，$\ldots$ $a_n$。玛丽娜想挑一束可能有最大花瓣总数的花束，且结果仍然是“爱”。帮她做到这一点：找到花瓣的最大数量可能在哪一个花束中。

## 样例 #1

### 输入

```
1
1
```

### 输出

```
1
```

## 样例 #2

### 输入

```
1
2
```

### 输出

```
0
```

## 样例 #3

### 输入

```
3
5 6 7
```

### 输出

```
13
```

# 题解

## 作者：绝顶我为峰 (赞：3)

这题真简单呀

~~可是还是没看题被卡了一次~~

直接用注释，不做详细解释了

```cpp
#include<iostream>
#include<algorithm>
using namespace std;
int n,k,a[101],m,ans;
int main()
{
    cin>>n;
    for(int i=1;i<=n;i++)
    {
        cin>>k;//输入花瓣数量
        if(k%2)//如果是奇数
            a[++m]=k;//存入数组
        ans+=k;//因为偶数不影响“爱”或“不爱”的结果，所以全部加上，不用存数组
    }
    if(m==0)//一个奇数都没有当然无法满足条件
    {
        cout<<0<<endl;//输出0
        return 0;
    }
    if(m%2==0)//如果有偶数个奇数
    {
        sort(a+1,a+m+1);//排序
        ans-=a[1];//去掉最小的一个，保证结果是“爱”
    }
    cout<<ans<<endl;//奇数个奇数不需变动，最后输出
    return 0;
}
```

---

## 作者：Neoomgg (赞：2)

本JR认为这是一道很水的题，思想和大佬们类似。但是个人认为中间的判断方法很特别，所以在此偷偷的来一发。

---

（上面是一条蟒蛇，嗯……）

```python
#Get the data in.
n = int(input())
a = list(map(int, input().split()))
sa = sum(a)
a.sort(reverse = True)

#Creat an main function and it'll be easy to stop the program.
def main(a, sa):
    #Check the number especially there's only one.
    if sa % 2 == 1:
        print(sa)
    else:
        #Everytime, pop 1 number (the most unusual part, think twice).
        for i in range(len(a)):
            if (sa - min(a)) % 2 == 1:
                print(sa - min(a))
                return
            else:
                a.pop()
        #Be careful!
        print(0)

#Call the function.
main(a, sa)
```

---

## 作者：Phykyer (赞：2)

一道标准的模拟水题  
花瓣个数为奇数是数到“爱”，偶数时为“不爱”  
反正模拟就过了
注释在代码

```
#include<iostream>
#include<algorithm>
using namespace std;

int n,a[101],p=0,ans=0;//a存每朵花花瓣数，p是奇数个数

int main()
{
    cin>>n;
    for(int i=1;i<=n;i++)
    {
        cin>>a[i];
        if(a[i]%2) p++;//统计有几朵是奇数个花瓣 
    }
    if(p==0) {cout<<0;return 0;}//如果奇数个数为0显然不可能数到爱 
    if(p%2)//如果奇数个花瓣的花数为奇数就全拿（可能有点拗口，自己理解一下……） 
    {
        for(int i=1;i<=n;i++) ans+=a[i];//统计花瓣总数 
        cout<<ans;
        return 0;
    }
    else
    {
        sort(a+1,a+n+1);//为偶数的花要去掉花瓣数为奇数中花瓣最少的一朵 
        for(int i=1;i<=n;i++) if(a[i]%2){a[i]=0;break;}//去掉 
		for(int i=1;i<=n;i++) ans+=a[i];//统计 
        cout<<ans;
    }
    return 0;/*perfect!*/ 
}
```

---

## 作者：Law_Aias (赞：1)

# 一道水题

就不加注释了，应该能看懂

```
#include<iostream>  
using namespace std;  
  
int main(){  
    int n,m,sum=0,a=101;  
    cin>>n;  
    while(n--){  
        cin>>m;  
        sum+=m;  
        if(m&1 && m<a) a=m;  
    }  
    if(sum&1) cout<<sum<<endl;  
    else{  
        if(a==101) cout<<0<<endl;  
        else cout<<sum-a<<endl;  
    }  
    return 0;  
}
```

实在想不明白为什么这种题有43个点？？？

---

## 作者：cq_loves_Capoo (赞：0)

这题的思路非常简单，大致如下：  
1.输入n，然后输入n个整数。   
2.对每个数进行奇偶性判断，如果为奇数，则用数组把这个数装住。   
3.求出所有数的和。   
4.如果没有奇数，输出0，退出程序。     
5.否则，判断奇数个数的奇偶性，如为奇数，减去最小的奇数，否则直接输出累加和。   
上AC代码：
```cpp
#include<bits/stdc++.h>//万能头文库
using namespace std;
int n,m,a[111],sum;//定义变量
int main()
{
	scanf("%d",&n);//输入n
	for(int i=1;i<=n;i++)
	{
		int s=0;//定义局部变量s
		scanf("%d",&s);//输入
		if(s%2) m++,a[m]=s;//把奇数存入数组
		sum+=s;//累加
	}
	if(!m) //判断如果没有奇数，输出0
	{
		printf("0");
		return 0;
	}
	m%2?printf("%d",sum):printf("%d",sum-*min_element(a+1,a+1+m));//如果奇数个数为奇数个，则减去最小奇数，然后输出累加和 
    //注：*min_element(a+1,a+1+m)为求一个数组的最小数语句
    return 0;//程序结束 
}
```


---

