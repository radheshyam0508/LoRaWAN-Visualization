# Web development

### Web 中代码的顺序：

HTML 中的代码顺序：

- 首先标准的DOCTYPE申明，html结构

   ~~~html
   <!DOCTYPE html>
    <html>
    <head></head>
    <body></body>
    </html>
   ~~~

  

- <head>中：

  HTML的<head>元素中一般有网页编码， <title>标题， <meta>描述网页关键字，<link>引入css文件， <script>引入javascript文件等。

  ~~~html
  <meta charset="utf-8">
          <title>IoT Fotonik</title> <!--the title of page bar-->
  <link rel="stylesheet" type="text/css" media="screen" href="style.css"/>
  ~~~

  Javascript 文件加在网页最底部

  

- <body>中：

  发挥<h1>...<p>之类的



CSS中代码的排序：例子

链接的交互排序

一个超链接，默认是蓝色的，当我们把鼠标移动上去，会变色，点击的过程也会变色，访问过后回来一看，通常也不会是原来的蓝色了。控制这些颜色的，分别是 CSS 中的 ：link 、：visited 、：hover、：active 这四个伪类选择器，从名称就可以看出，控制的状态分别是：默认显示、访问过后、鼠标移动上去、点击激活。有时候会出现一些意外情况，例如：同时设置了 ：visited 和 ：hover 的样式，但一旦超链接访问后，hover 的样式就不出现了等。这是因为，这四个伪类选择器对 a 元素定义的时候，是有一个顺序的。如果不按照这个顺序，就会出现一些意外情况。

这个顺序有一个很好记的方法，那就是：love hate，即 l（link）ov（visited）e h（hover ）a（active）te。

~~~css
  a:link{color:#666666; text-decoration:none;}
  a:visited{color:#666666; text-decoration:none;}
  a:hover{color:#666666; text-decoration:underline;}
  a:active{color:#666666; text-decoration:none;}
~~~



Javascript代码的顺序：

**JavaScript 文件加载顺序**

jQuery 是一个比较常用的 JavaScript 库，通常我们还要配合它强大的插件使用。对于新手来说，经常会遇到没有产生相应效果的问题。就是说，代码没有检查出问题，但就是没有执行显示应有的效果。原因就出在加载顺序上面。你编写的 JavaScript 代码以及调用的 jQuery 插件，都需要基于 jQuery 库，所以应该在所有 JavaScript 代码之前，先引入 jQuery 库。浏览器先把库下载完了，才会识别后面的依赖这个库的代码实现相应的功能。同样的，激活使用某个插件的代码，也需要放在插件的后面才会有效。

~~~javascript
  <script type="text/javascript" src="http://lib.sinaapp.com/js/jquery/1.7.2/jquery.min.js"></script>
  <script type="text/javascript" src="jquery/jquery.lazyload.js"></script>
  <script type="text/javascript" src="jquery/插件.js"></script>
  <script type="text/javascript" src="自己编写的js/js.js"></script>
~~~



JavaScript 是目前所有主流浏览器上唯一支持的脚本语言，这也是早期JavaScript的唯一用途。其主要作用是在不与服务器交互的情况下修改HTML页面内容，因此其最关键的部分是DOM（文档对象模型），也就是HTML元素的结构。通过Ajax可以使HTML页面通过JavaScript，在不重新加载页面的情况下从服务器上获取数据并显示，大幅提高用户体验。通过JavaScript，使Web页面发展成胖客户端成为可能。

