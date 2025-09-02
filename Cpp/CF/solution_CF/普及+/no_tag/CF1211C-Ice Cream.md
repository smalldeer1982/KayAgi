# Ice Cream

## 题目描述

Tanya 想在 $n$ 天内吃掉 $k$ 份冰淇凌，在第 $i$ 天她至少吃 $a_i$ 份，至多吃 $b_i$ 份，冰淇凌的价格为 $c_i$，当天买必须当天吃完，求最少的花费。

## 样例 #1

### 输入

```
3 7
3 5 6
0 3 4
3 3 3
```

### 输出

```
31
```

## 样例 #2

### 输入

```
1 45000
40000 50000 100000
```

### 输出

```
4500000000
```

## 样例 #3

### 输入

```
3 100
2 10 50
50 60 16
20 21 25
```

### 输出

```
-1
```

## 样例 #4

### 输入

```
4 12
2 5 1
1 2 2
2 3 7
3 10 4
```

### 输出

```
35
```

# 题解

## 作者：Lpttor (赞：2)

很简单的贪心题。

先把每天至少要吃的买了，剩下的按价格排序，然后从小到大买。

注意特判一下无解的情况，还有要开Long.

AC代码：

```kotlin
import java.util.Scanner
//用Scanner可以直接nextInt,就不用考虑太多输入格式了
data class days (var mx:Long,var cost:Long)
fun min(a:Long,b:Long):Long{
    if(a>b) return b
    else return a
}
fun main(args: Array<String>){
    val sc=Scanner(System.`in`)
    var n=sc.nextInt()
    var k=sc.nextLong()
    var ans=0L
    var mn:Long
    var mx:Long
    var cost:Long
    var arr:MutableList<days> = mutableListOf()
    for (i in 0..n-1) {
        mn=sc.nextLong()
        mx=sc.nextLong()
        cost=sc.nextLong()
        k-=mn
        mx-=mn
        ans+=cost.toLong()*mn
        arr.add(days(mx,cost))
    }
    if(k<0){
        println(-1)
        return
    }
    arr.sortBy { it.cost }
    for(it in arr){
        ans+=min(k,it.mx).toLong()*it.cost
        k-=it.mx
        if(k<=0) break
    }
    if(k>0) println(-1)
    else println(ans)
}
```

---

