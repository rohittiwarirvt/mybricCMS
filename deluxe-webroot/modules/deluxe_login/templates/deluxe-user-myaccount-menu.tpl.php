
<div class="control-panel">
<div class="info-panel clearfix">
    <div class="user-name">Hello, <span id="UserFirstName"><?php if(isset($_SESSION['FirstName'])) print $_SESSION['FirstName']; else print "Guest";?></span></div>
    <div class="my-account has-dropdown" id="login-dropdown">
        <a href="/myaccount">My Account</a>
        <div class="dropdown">
            <?php print $user_menu_data['menu_list']; ?>
            <div class="arrow-top"></div>
        </div>
    </div>
    <div class="cart">
        <a href="/shoppingcart">
            Cart (<span id="CartItemsCount">0</span>)
        </a>
    </div>
    <?php if(isset($user_menu_data['chat'])): ?>
     <div class="chat-wrapper">
            <span class="chat">
                Chat
            </span>
     </div>
    <?php endif;?>
    <div class="phone"><?php print $user_menu_data['tenant_phone']; ?></div>
</div>
</div>
