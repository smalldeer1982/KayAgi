# 「LAOI-6」[太阳]] 请使用最新版手机 QQ 体验新功能

## 题目背景

「」

---

![](https://cdn.luogu.com.cn/upload/image_hosting/05xcfhr8.png)

## 题目描述

你的 QQ 收到了一条新消息！但是你很生气，因为你看不到别人发送的超级表情。

消息形如一个字符串 $S$，包含且仅包含一个超级表情。具体地，$S$ 的拼音被采用驼峰命名法处理，因此其形如：

```plain
[AaaBbbCcc......]]QingShiYongZuiXinBanShouJiQQTiYanXinGongNeng
```

也就是说，将 $\texttt [w\texttt{]]请使用最新版手机QQ体验新功能}$ 中的每个汉字替换为其拼音，其中 $w$ 为表情的实际中文名称，保证其包含至少一个音节，**其中每个音节包含一个大写英文字母和至少一个小写英文字母**。

你想在电脑上也能发出这个表情。为此，你需要键入一个正斜杠（$\texttt /$）加它的「拼音缩写」。**具体地，表情 $\bm w$ 的「拼音缩写」即为 $\bm w$ 的每个音节的首字母转为小写后拼接的结果**。例如，`TaiYang` 的「拼音缩写」为 $\texttt{/ty}$，而 `YueLiang` 的「拼音缩写」为 $\texttt{/yl}$。

请你输出在电脑端表示发送这个表情的字符串。

请注意：这个字符串可能在 QQ 中实际上不能表示这个表情，例如 `NiZhenBangBang`（一个超级表情） 不能在 QQ 中用 $\texttt{/nzbb}$ 来打出，但是在本题中，我们认为其是合法的。

## 说明/提示

**本题采用捆绑测试。**

对于 $100 \%$ 的数据，保证给出的字符串 $S$ 满足题目中所写的 `[AaaBbbCcc......]]QingShiYongZuiXinBanShouJiQQTiYanXinGongNeng` 的格式，且保证 $\lvert S\rvert \leq 100$；给出的 $S$ 描述一个真实存在的 QQ 超级表情。

## 样例 #1

### 输入

```
[TaiYang]]QingShiYongZuiXinBanShouJiQQTiYanXinGongNeng```

### 输出

```
/ty```

## 样例 #2

### 输入

```
[LiuLei]]QingShiYongZuiXinBanShouJiQQTiYanXinGongNeng```

### 输出

```
/ll```

# 题解

## 作者：luogu_gza (赞：26)

官方题解（（（

考虑到我们实际上输出的是第一个 `]` 号之前的所有大写字母转为小写字母的结果，因此直接写出下面的代码（仅给出关键部分）：

```cpp
string s;
void main(){
  cin>>s;
  putchar('/');
  for(auto i:s)
    if(i==']') break;
    else if(isupper(i)) putchar(i-'A'+'a');
}
```

其中 `isupper` 这个函数是用于判断一个字符是否为大写字母，`putchar` 函数则是用于输出一个 `char`。

---

