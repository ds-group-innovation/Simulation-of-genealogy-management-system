
/*视频播放*/
    var video = $("#videoModal #video")[0];
    $("#videoModal").modal("show");
    $("#videoModal").modal("hide");
    $(".viewLive").on("click",function(){
        video.play();
    });
    var isPaly = true;
    $("#videoModal #video").on("click",function(){
        if(isPaly){
            video.pause();
            isPaly = false;
        }else{
            video.play();
            isPaly = true;
        }
    });
    $("#videoModal").on('hidden.bs.modal',function(){
        video.pause();
    });
/*视频播放 end*/


$(function(){
    /*海报区域翻页动画*/
    $('.box_skitter_large').skitter({
        theme: 'clean',
        numbers_align: 'center',
        // progressbar: true,   时间计时条
        dots: true,     //按钮条
        preview: true
    });
    /*海报区域翻页动画 end*/

    /*最新资讯*/
    $(".news li").css({"left":"0","opacity":"1"});
    /*最新资讯 end*/

    /*机构设置*/
    $(window).scroll(function(){
        addclass(".instituList");
        addclass(".index-teacher-main");
    });
    function addclass(e){
        var win_h = $(window).height()*0.75;
        var t = $(e).offset().top;
        var top = $(window).scrollTop();
        if(top>t-win_h){
            $(e).addClass("on");
        }
    }
    /*机构设置 end*/

    /*指导老师轮播*/
    var ti = 0;
    var indexTeacherItem = $(".index-teacher .teacherItem");
    for(var j=0;j<4;j++){
        indexTeacherItem.find("li").eq(j).clone().appendTo(".index-teacher .teacherItem");
    }
    var size = indexTeacherItem.find("li").size()-3;
    //自动轮播
    var teacherTimer = setInterval(function(){
        ti++;
        move();
    },3000);
    //对自动轮播定时器的操作
    $(".index-teacher").hover(function(){
        clearInterval(teacherTimer);
    },function(){
        teacherTimer = setInterval(function(){
            ti++;
            move();
        },3000);
    });
    //向左按钮
    $(".index-teacher .btn_l").click(function(){
        ti--;
        move();
    });
    //向右按钮
    $(".index-teacher .btn_r").click(function(){
        ti++;
        move();
    });
    function move(){
        if(ti==size){
            indexTeacherItem.css({left:0});
            ti=1;
        }
        if(ti==-1){
            indexTeacherItem.css({left:-(size-1)*260});
            ti=size-2;
        }
        indexTeacherItem.stop().animate({left:-ti*260},500);
    }
    /*指导老师轮播 end*/
});