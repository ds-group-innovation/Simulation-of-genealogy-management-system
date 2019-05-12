
$(function(){
/*侧边栏导航跟随条*/
    // var li_height = $(".detailContent .leftNav li a.on").outerHeight()+1;
    // var li_top = $(".detailContent .leftNav li a.on").position().top;
    // var line = $(".detailContent .leftNav .detailLine");
    // line.css({height:li_height,top:li_top});

    // $(".detailContent .leftNav li").hover(function(){
    //     var li_height = $(this).outerHeight();
    //     var li_top = $(this).position().top;
    //     line.stop().animate({height:li_height,top:li_top},{duration:500,easing:"easeInOutCubic"});
    // },function(){
    //     line.stop().animate({height:li_height,top:li_top},{duration:500,easing:"easeInOutCubic"});
    // });

    // $("#leftNavDown").click(function(){
    //     $(this).toggleClass("icon-ic_remove icon-ic_add");
    //     $(".leftNavDown").slideToggle();
    // });

/*侧边栏导航跟随条 end*/

/*侧边栏导航定位*/
    var jWindow = $(window);
    var leftNav = $(".leftNav");
    var contentHeight = $(".column_2").height();    /*获取内容高度*/
    var leftNavHeight = leftNav.offset().top;       /*获取左侧导航栏离浏览器窗口的高度*/
    jWindow.scroll(function(){
        var scrollHeight = jWindow.scrollTop();     /*获取滚动条离顶端距离，即鼠标滑动距离*/
        if(scrollHeight > leftNavHeight && scrollHeight < contentHeight){
            leftNav.css("top",scrollHeight - leftNavHeight + 16 + "px");        /*固定滚动条*/
        }else if(scrollHeight <= leftNavHeight){
            leftNav.css("top","16px");              /*如果滚动条往上滚动太快起作用*/
        }else{
            leftNav.css("top",contentHeight - leftNavHeight + 16 +"px");
        }                                           /*如果滚动条往下滚动太快起作用*/
    });
/*侧边栏导航定位 end*/
});

