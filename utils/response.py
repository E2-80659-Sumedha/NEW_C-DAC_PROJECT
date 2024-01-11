from flask import jsonify

def create_response(data, error=None):
    # create empty dictionary
    d = dict()

    if(error == None):
        d = {
            "status":"success",
            "data":data
        }
    else:
        d = {
            "status":"failure"
        }

    return jsonify(d)