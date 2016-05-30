;(function($) {

     var rScroll = function(elem,options){
        this.elem = elem;
        this.waitState = false;
        this.current_page = 0;
        this.loaderDivId = "_rSroll-loader-div";
        this.options = $.extend(this.defaults,options);
        this.appendDom = this.options.appendDom;
        this.loaderDom = this.options.loaderDom;
        this.params = this.options.params;
        this.url = this.options.url;
        this.init();
     }

     rScroll.prototype.defaults = {
        url : "",
        sendData : null,
        params : {},
        appendDom : "<small>Loading..</small>"
     }

     rScroll.prototype.init = function(){
        var __self = this;

     //   __self.loadpage();
        $(document).scroll(function(){
          if ($(document).scrollTop() >=$(document).innerHeight()*1-1800){//added 50 for not to wait scroll to bottom
    
            __self.loadpage();
          }
        });
     }

     rScroll.prototype.loadpage = function(){

        var __self = this;
      
        if(__self.waitState) return;

        __self.waitState = true;

        $(__self.elem).append('<div id="'+__self.loaderDivId+'" style="width:100%;text-align: center;">'+ __self.loaderDom +'</div>');

        __self.loadMore(__self.current_page,function(data){
            if(!data) return;

            __self.current_page ++;

            $(__self.elem).find('#'+__self.loaderDivId).remove();

            if(typeof __self.appendDom == 'function'){
              __self.appendDom(data)
            }
            __self.waitState = false;
        });
     }

     rScroll.prototype.loadMore = function(current_page,cb){
        var __self = this;
        var params = __self.params;
        params.current_page = current_page;
        
        params = 'json='+JSON.stringify(params);

        $.ajax({
            method:'get',
            url:__self.url,
            data:params,
            success: function(data){
                return cb(data);
            },
            error: function(err){
                return cb();
            }
        });
      
     }

    $.fn.rScroll = function(options){
      return this.each(function(){
        new rScroll(this,options);
      });
    };

})(jQuery);