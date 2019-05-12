

/*头部定位页面*/
var index = window.location.href.split("/").length-1;   //获取地址栏的地址，用/分割成一个数组，获取最后一个"索引"
var href = window.location.href.split("/")[index].substr(0,4);  //当前html的文件名的前4个字符
$(".header .nav1 li a[href^='"+href+"']").addClass("on");
/*头部定位页面 end*/

/*头部导航下拉框动画*/
$(".header .nav1 li").hover(function(){
    $(this).find(".nav1-down").stop().slideToggle({duration:600,easing:'easeOutBack'});
});
/*头部导航下拉框动画 end*/

/*侧边栏导航定位*/
var detailhref = window.location.href.split("/")[index];
// var abouthref = window.location.href.split("/")[index].substr(0,7);
// var institutionhref = window.location.href.split("/")[index].substr(0,13);
// var newshref = window.location.href.split("/")[index].substr(0,6);
// var communicatehref = window.location.href.split("/")[index].substr(0,13);

function leNav(ihref){
    $(".detailContent .leftNav li a[href^='"+ihref+"']").addClass("on");
}
leNav(detailhref);

/*侧边栏导航定位 end*/


/*回到顶部功能*/
$(function(){
    if($(window).scrollTop()>161){
        $(".top").fadeIn();
    }
    $(window).scroll(function(){
        $(window).scrollTop()>161?$(".top").fadeIn():$(".top").fadeOut();
    });
    $(".top").click(function(){
        $("body,html").stop().animate({scrollTop:0},300);
    });
});
/*回到顶部功能 end*/

