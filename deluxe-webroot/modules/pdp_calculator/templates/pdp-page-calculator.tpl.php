<div data-bind="visible: true, loading: isLoaderVisible" class="main" style="display: none">
    <!--    <div data-bind="visible: productName" style="margin: 50px; font-size: 18px;">
           Product name: <span data-bind="text: productName"></span>
       </div> -->

       <div class="promo-wrapper has-bg">
           <div class="page-width">
               <div class="table-wrapper clearfix">
                   <div class="table-item" id="calc">
                    <div class="table-tool pdp-tool">
                      <div class="table-caption">
                        <div class="table-cell options">Product Options</div>
                        <div class="table-cell options">Design &amp; Proofing</div>
                        <div class="table-cell options">Production &amp; Shipping</div>
                      </div>
                      <div class="table-body">
                        <div class="table-cell options">
                          <div id="options-container"></div>

                          <div class="bottom-link">
                            <a data-bind="toggle: isProductOptionsDialogVisible"
                               id="product-options-link" href="javascript:void(0);">
                              <span class="ui-button-text">Product Options Details</span>
                            </a>
                          </div>
                        </div>
                        <div class="table-cell options">
                          <div class="radio-wrapper clearfix">
                            <label>Upload Design (Optional)</label>
                          </div>

                          <div data-bind="css: { 'upload-wrapper uiwfileupload upload-unavailable': !catalogId() }">
                            <!-- ko if: catalogId -->
                            <div data-bind="fileUploadWidget: {}, observables: fileUploadOptions, events: fileWidgetEvents" class="upload-wrapper"></div>
                            <!-- /ko -->
                          </div>

                          <div id="proofing"></div>

                          <div class="bottom-link">
                            <a data-bind="toggle: isProofingDialogVisible" id="proofing-link" href="javascript:void(0);">
                              <span class="ui-button-text">Design &amp; Proofing Details</span>
                            </a>
                          </div>
                        </div>
                        <div class="table-cell options">
                          <div id="turnaround"></div>

                          <!-- ko ifnot: PsPrintApp.isEquantum -->
                          <div class="select-wrapper radio-wrapper clearfix" data-bind="visible: isMailOptionAvailable">
                            <label>Delivery Method</label>
                            <div class="radio-group">
                              <input id="ship-delivery" name="ship-delivery" type="radio" value="ship" data-bind="checked: deliveryMethod">
                              <label for="ship-delivery">Ship it</label>
                              <input id="mail-delivery" name="ship-delivery" type="radio" value="mail" data-bind="checked: deliveryMethod">
                              <label for="mail-delivery">Mail Services</label>
                            </div>
                          </div>

                          <div class="clearfix" data-bind="stopBinding: true, visible: isShipDeliveryMethod" id="shipping-container"></div>

                          <div data-bind="hidden: isShipDeliveryMethod">
                            <div id="mailing"></div>
                          </div>

                          <div class="arrival-date" data-bind="visible: arrivalDate() && isShipDeliveryMethod()">
                            Estimated Arrival Date: <span data-bind="text: arrivalDate"></span>
                          </div>
                          <div class="arrival-date" data-bind="visible: mailDate() && !isShipDeliveryMethod()">
                            Estimated Mail Date: <span data-bind="text: mailDate"></span>
                          </div>
                          <div class="text note" data-bind="visible: weightThresholdExceded() && !PsPrintApp.currentStore.isWholesale">Due to the large size of your order, other shipping options may be more economical. Please contact a customer support representative at 800.511.2009 for further options</div>
                          <div class="text note" data-bind="visible: showPickup"><b>Need it faster?</b> You can pick up your order for free. <a data-bind="click: setPickup" href="javascript:void(0);">Click here</a> to update your shipping option.</div>
                          <div class="text note" data-bind="visible: showFreight"><b>Want to ship via Freight?</b> <a data-bind="toggle: isFreightLearnMoreDialogVisible" href="">Click here</a> to learn more.</div>

                          <div class="bottom-link">
                            <a data-bind="toggle: isDeliveryOptionsDialogVisible" id="delivery-options-link"
                               href="javascript:void(0);">Delivery Options Details</a>
                          </div>
                          <!-- /ko -->
                        </div>
                      </div>
                    </div>
                  </div>
                   <div class="table-item">
                       <div class="table-tool">
                           <div class="table-caption">
                               <div class="table-cell summary">Job Summary</div>
                           </div>
                           <div class="table-body">
                               <div class="table-cell summary">
                                   <div class="cost clearfix">
                                       <div class="item">Printing Cost:</div>
                                       <div class="value"><span data-bind="currency: baseCost"></span></div>
                                   </div>
                                   <div class="off clearfix" data-bind="visible: discount">
                                       <div class="item">
                                           <span data-bind="text: discountPercent"></span>
                                           Off<span class="discount-maximum" data-bind="visible: maximumDiscount">
                                               (up to $<span data-bind="text: maximumDiscount"></span>)
                                           </span>:
                                       </div>
                                       <div class="value">- <span data-bind="currency: discount"></span></div>
                                   </div>
                                   <div class="mailing clearfix" data-bind="visible: !isShipDeliveryMethod() && mailingCost()">
                                       <div class="item">Mailing Service:</div>
                                       <div class="value"><span data-bind="currency: mailingCost"></span></div>
                                   </div>
                                   <div class="shipping clearfix" data-bind="visible: isShipDeliveryMethod() && !PsPrintApp.isEquantum">
                                       <div class="item">Shipping:</div>
                                       <div class="value"><span data-bind="currency: shipCost"></span></div>
                                   </div>
                                   <div class="tax clearfix" data-bind="visible: tax">
                                       <div class="item">Tax:</div>
                                       <div class="value"><span data-bind="currency: tax"></span></div>
                                   </div>
                                   <div class="total clearfix">
                                       <div class="item">Job Total:</div>
                                       <div class="value"><span data-bind="currency: total"></span></div>
                                   </div>
                               </div>
                           </div>
                          <div data-bind="visible: catalogId() && baseCost()" class="table-body" style="display: none">
                            <div class="table-cell summary">
                                   <input data-bind="click: addToCart, css: { disabled: isComet && isAddToCartDisabled() }, disable: isAddToCartDisabled" class="add-to-cart" type="button" value="Add to Cart" disabled />
                            </div>
                          </div>
                          <div data-bind="visible: displayCopyBlock()" class="copy-block">
                                <div class="inner-header">Die-Cut Product Note:</div>
                                <div class="inner-content">
                                    Non-standard dies are not included in the price above.<br />
                                    Additional costs can be $100 and up depending on complexity.
                                </div>
                          </div>
                        </div>
                   </div>
               </div>
           </div>
       </div>
   </div>

   <div data-bind="dialog: messageDialogOptions, dialogVisible: isMessageDialogVisible"
         class="dialog-window message-dialog" style="display: none">
       <div class="title" data-bind="text: messageDialogTitle"></div>
       <div class="content">
           <!-- ko if: !messageDialogContent() -->
           <p>Opps! That’s an invalid file type. We accept the following formats:</p>
           <p class="pre">     • .JPG          • .TIF                  • .PSD<br>      • .PS                   • .EPS                  • .PNG<br>      • .PDF</p>
           <!-- /ko -->
           <!-- ko if: messageDialogContent -->
           <span data-bind="html: messageDialogContent"></span>
           <!-- /ko -->
       </div>
       <div class="arrow arrow-top"></div>
   </div>

   <!-- ko with: myFiles -->
   <div data-bind="dialog: { dialogClass: '' }, dialogVisible: isVisible, loading: isLoading" class="modal-window" style="display: none">
       <div class="myfiles-container">
           <h2 class="title">My Files</h2>
           <div data-bind="visible: noRecords" class="myartwork-norecordspan">No records to display</div>
           <div data-bind="hidden: noRecords">
               <div style="line-height: 24px;">
                   <span>Select a file for your Job.</span>
                   <div style="float: right">
                       <input data-bind="textInput: keywordSearch, enterkey: search" title="Search using Keyword\Color\Name" type="text" placeholder="Search using Keyword\Color\Name" class="myartwork-txtsearchmedia">
                       <img data-bind="click: search" class="myartwork-btnsearch" title="Search" alt="Search" src="/Content/img/MyAccount/search-icon-myartwork.png">
                       <img data-bind="click: reset" class="myartwork-btnreset" title="Clear Search Results" alt="Reset" src="/Content/img/MyAccount/nav-reset-icon.png">
                   </div>
               </div>
               <div data-bind="component: { name: 'paginator', params: { total: totalRecords, pageSizeOptions: [6, 12], pages: 5, pageSize: pageSize, page: pageNumber, onPaging: reload.bind($data)} }" class="customerjobs-pagination-wrapper top"></div>
               <div data-bind="visible: myFiles().length != 0" class="myartwork-tbl_main">
                   <div class="myartwork_gallery-wrapper clearfix" style="padding-left:43px">
                       <!-- ko foreach: myFiles -->
                       <div class="myaccount-myartwork-div-items">
                           <input data-bind="value: fileName" type="text" class="myartwork-artworkdisplay-selectmyfilesdisplayFilename" />
                           <div class="myartwork-item-image-wrapper">
                               <div class="myartwrok-artworkdisplay-GriddivThumbImg">
                                   <div class="myartwork-artworkdisplay-imagediv">
                                       <span class="myartwork-artworkdisplay-thumbimagespan">
<img src="data:image/gif;base64,R0lGODlhAQABAIAAAAAAAP///yH5BAEAAAAALAAAAAABAAEAAAIBRAA7" alt="" data-bind="attr:{ src: PsPrintApp.apiEndPoints.Files.thumbnail + mediaID }" class="myartwork-artworkdisplay-thumbimage" />                                       </span>
                                   </div>
                               </div>
                           </div>
                           <div data-bind="date: creationDate" class="myaccount-myartworkfooter"></div>

                           <div class="myartwork-artworkdisplay-alignselectbutton">
                               <input data-bind="click: $parent.selectFile.bind($parent)" type="button" class="myartwork-selectbutton" value="Select" />
                           </div>
                       </div>
                       <!-- /ko -->
                   </div>
               </div>
           </div>
       </div>
   </div>
   <!-- /ko -->

   <div data-bind="dialog: { dialogClass: '' }, dialogVisible: isFreightLearnMoreDialogVisible" class="pdp-popup modal-window" style="display: none">
       <div class="window-title">Freight</div>
       <div class="table-details wide clearfix">
           <div class="detail-item">
                 <div class="detail-content">
                    <p>Upon receipt of your freight request, <!-- ko text: PsPrintApp.currentStore.communityName --><!-- /ko --> will notify you via email that your request has been received. An email notification will be sent to you when your freight quote has been added to your saved quote.</p>
                    <p>To purchase the quote, log back into <!-- ko text: window.location.hostname --><!-- /ko --> and view the cost on your saved quote. If you accept freight cost, then you will need to “check out” and place your order.</p>
                    <p>*Additional charges may apply for liftgate/guaranteed service, please email <!-- ko text: PsPrintApp.currentStore.customerServiceEmail --><!-- /ko --> with any special requests or requirements referencing your quote number.</p>
               </div>
           </div>
       </div>
   </div>

   <div data-bind="dialog: { dialogClass: '' }, dialogVisible: isProductOptionsDialogVisible" class="pdp-popup modal-window" style="display: none">
       <div class="window-title">
           <!-- ko text: productName --><!-- /ko --> Printing Options
       </div>
       <div class="table-details wide clearfix">
           <!-- ko foreach: catalogOptionDescriptions -->
           <div class="detail-item">
               <div data-bind="text: name" class="detail-title"></div>
               <div data-bind="css: { 'two-columns image': !iconPath }" class="pseudo-table">
                   <div class="table-row">
                       <div data-bind="text: description" class="table-cell"></div>
                       <div class="table-cell">
                           <!-- ko if: iconPath -->
                          <img src="data:image/gif;base64,R0lGODlhAQABAIAAAAAAAP///yH5BAEAAAAALAAAAAABAAEAAAIBRAA7" alt="" data-bind="attr:{ alt: name, title: name, src: iconPath }" />
                          <!-- /ko -->
                       </div>
                   </div>
               </div>

               <!-- ko foreach: choices -->
               <div class="pseudo-table three-columns">
                   <div class="table-row">
                       <div data-bind="text: name" class="table-cell"></div>
                       <div data-bind="text: description" class="table-cell"></div>
                       <div class="table-cell">
                           <!-- ko if: iconPath -->
                          <img src="data:image/gif;base64,R0lGODlhAQABAIAAAAAAAP///yH5BAEAAAAALAAAAAABAAEAAAIBRAA7" alt="" data-bind="attr:{ alt: name, title: name, src: iconPath }" />
                           <!-- /ko -->

                           <!-- ko ifnot: iconPath -->
                               <span data-bind="html: specification"></span>
                           <!-- /ko -->
                       </div>
                   </div>
               </div>
               <!-- /ko -->
           </div>
           <!-- /ko -->
       </div>
   </div>

   <div data-bind="dialog: { dialogClass: '' }, dialogVisible: isProofingDialogVisible" class="pdp-popup modal-window" style="display: none">
       <div class="window-title">Design &amp; Proofing Options</div>
       <div class="table-details clearfix">
           <div class="detail-item">
               <div class="detail-title">Upload Design</div>
               <div class="detail-content">
                   <p>You can upload your art and preview your piece before you order.</p>
               </div>
               <div class="pseudo-table two-columns">
                   <div class="table-row">
                       <div class="table-cell">Now</div>
                       <div class="table-cell">You may upload a new file or select artwork you have saved in your account using the upload widget on the product detail page.</div>
                   </div>
                   <div class="table-row">
                       <div class="table-cell">Later</div>
                       <div class="table-cell">You may still purchase your order now and upload your artwork after payment.</div>
                   </div>
               </div>
           </div>
          <div data-bind="visible: isProofAvailable" class="detail-item">
              <div class="detail-title">Proofing</div>
               <div class="detail-content">
                   <p>For a small additional charge, you can order a printed proof. You will receive up to 3 hardcopy proof revisions and a color accuracy guarantee on the final proof that is approved by you.</p>
               </div>
               <div class="pseudo-table two-columns">
                   <div class="table-row">
                       <div class="table-cell">No Hardcopy</div>
                       <div class="table-cell">Process my order without a hardcopy proof.</div>
                   </div>
                   <div class="table-row">
                       <div class="table-cell">Standard Hardcopy</div>
                       <div class="table-cell">Send me a hardcopy proof via standard shipping for approval. Keep in mind a hardcopy proof can extend your project's timeline but is the best way to ensure your final printed piece looks exactly as you desire.</div>
                   </div>
                   <div class="table-row">
                       <div class="table-cell">Next-Day Hardcopy</div>
                       <div class="table-cell">Send me a hardcopy proof via next-day shipping for approval. Keep in mind a hardcopy proof can extend your project's timeline but is the best way to ensure your final printed piece looks exactly as you desire.</div>
                   </div>
               </div>
              <div class="pseudo-table one-column">
                      <div class="table-row">
                      <div class="table-cell"><strong>Please note: </strong>Your proof will be shipped to the billing address for your order. If you would like to pick up your proofs at one of our local facilities, or have your proofs shipped to another address, please put a note on your order with the updated address. At this time, we are not able to ship to P.O. Box addresses, so if the contact information on your account is a P.O. Box, please put a note with a new shipping address on your order otherwise your proof will be delayed.</div>
                      </div>
                  </div>
           </div>
       </div>
   </div>

   <div data-bind="dialog: { dialogClass: '' }, dialogVisible: isDeliveryOptionsDialogVisible" class="pdp-popup modal-window" style="display: none">
       <div class="window-title">Delivery Option Details</div>
       <div class="table-details clearfix">
           <div class="detail-item">
               <div class="detail-title">Production Time</div>
               <div class="detail-content">
                   <p>This option allows you to choose how long your order will take to produce, pack and prepare for shipping, mailing or pickup.</p>
               </div>
           </div>
           <div class="detail-item">
               <div class="detail-title">Delivery Method</div>
               <div class="detail-content">
                   <p>You can choose to have your order shipped to you, or for certain products you can choose to send your pieces to an individual  address from a mailing list. This option will only be available if your ordered product meets the mailing requirements.</p>
               </div>
           </div>
           <div class="detail-item">
               <div class="detail-title">Ship to</div>
               <div class="detail-content">
                   <p>Please enter the zip code you would like your order shipped to. It will be used to provide you with a shipping price.</p>
               </div>
           </div>
           <div class="detail-item" data-bind="visible: shipCost">
               <div class="detail-title">Shipping Option</div>
               <div class="detail-content">
                   <p>The shipping option you choose combined with the production time choice you make will determine how soon you will receive your order.</p>
               </div>
               <div class="pseudo-table two-columns">
                   <div class="table-row" data-bind="visible: isPickupAvailable">
                       <div class="table-cell">Pickup (Free)</div>
                       <div class="table-cell">Choose this option to pick up your order at your local facility for no charge.</div>
                   </div>
                   <div class="table-row">
                       <div class="table-cell">Ground</div>
                       <div class="table-cell">Ship your order via standard service. Delivery time varies by your delivery zip code and the location your order ships from.</div>
                   </div>
                   <div class="table-row">
                       <div class="table-cell">Two Day</div>
                       <div class="table-cell">Ship your order via Two Day service. Your order will be in transit for 2 days after shipping.</div>
                   </div>
                   <div class="table-row">
                       <div class="table-cell">Next Day</div>
                       <div class="table-cell">Ship your order via Next Day service. Your order will be in transit for 1 day after shipping.</div>
                   </div>
               </div>
           </div>
           <div class="detail-item" data-bind="visible: isMailOptionAvailable">
               <div class="detail-title">Mailing Option</div>
               <div class="detail-content">
                   <p>The mailing option you chose combined with the production time choice you make will determine how soon your pieces will arrive in mailboxes.</p>
               </div>
               <div class="pseudo-table two-columns">
                   <div class="table-row">
                       <div class="table-cell">First Class Mailing</div>
                       <div class="table-cell">For faster delivery to individuals chose this option, which typically takes from 3-5 business days.</div>
                   </div>
                   <div class="table-row">
                       <div class="table-cell">Standard Mailing</div>
                       <div class="table-cell">For more economical delivery to individuals chose this option, which typically takes from 4-10 business days.</div>
                   </div>
               </div>
           </div>
           <div class="detail-item">
               <div class="detail-title">Estimated Arrival</div>
               <div class="detail-content">
                   <p>This is the anticipated date you will receive your order or when it will be ready for pickup.  If you have chosen to mail your pieces it will show the estimated delivery dates to the recipients on your list.</p>
                   <p>It is based on the time you upload your design, and the combination of your chosen production time and your shipping or mailing option.</p>
                   <p>If you need your order before this date, we suggest upgrading to a faster shipping method/mailing speed or production time.</p>
                   <p>Example: You chose a 3-day production time and UPS Two Day shipping, your order will arrive 5 business days after you upload your design.</p>
               </div>
           </div>
       </div>
   </div>

<?php
  drupal_add_js('/httphandler/bundle/common-wholesale', array('scope' => 'footer','type' => 'external', 'weight' => 1));
  drupal_add_js('/httphandler/PsPrintAppInit', array('scope' => 'footer','type' => 'external', 'weight' => 2));
  drupal_add_js('/httphandler/bundle/knockout', array('scope' => 'footer','type' => 'external', 'weight' => 3));
  drupal_add_js('/httphandler/bundle/widgets-v2', array('scope' => 'footer','type' => 'external', 'weight' => 4));
  drupal_add_js('//files.psprint.com/javascripts/uiWidgetManagerNextGen.js', array('scope' => 'footer','type' => 'external', 'weight' => 5));
  drupal_add_js('/httphandler/bundle/product-detail-drupal', array('scope' => 'footer','type' => 'external', 'weight' => 6));

  drupal_add_js('$(".megamenu-parent").on("mouseenter", function() {
        $("select").blur();
    });',array('type' => 'inline', 'scope' => 'footer', 'weight' => 7));

  drupal_add_js("
      if (typeof $ === 'undefined' || typeof $.fn.catalogOptions === 'undefined') {
       document.location.reload(true);
      }", array('type' => 'inline', 'scope' => 'footer', 'weight' => 8)
    );
      drupal_add_css('/Content/css/MyAccount.css', array('type' => 'external', 'scope' => 'footer', 'weight' => -1));
    drupal_add_css('/Content/css/Site.css', array('type' => 'external', 'scope' => 'footer', 'weight' => -1));
    drupal_add_css('https://files.psprint.com/stylesheets/uiwidget.css', array('type' => 'external', 'scope' => 'footer', 'weight' => -1));
?>
