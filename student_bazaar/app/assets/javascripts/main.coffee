exports = this

exports.notification = (msg, type) ->
  if typeof type == 'undefined'
    type = 'primary'
  if type == 'alert'
    type = 'warning'

  n = noty
    layout: 'top'
    text: msg
    type: type
    dismissQueue: true
    maxVisible: 1
    timeout: 8000
  return