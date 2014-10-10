function fw_flag_change(image, flag)
{
  var element = document.getElementsByName(image)[0];
  var directory = element.src.substring(0, element.src.lastIndexOf("/") + 1);
  element.src = directory + flag + element.src.substring(element.src.lastIndexOf("."));
}