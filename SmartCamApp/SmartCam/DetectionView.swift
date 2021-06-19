//
//  DetectionView.swift
//  SmartCam
//
//  Created by Jasson Rodríguez Méndez on 18/6/21.
//

import SwiftUI

struct DetectionView: View {
    @StateObject var httpRequests = RequestManager()
    var body: some View {
        VStack(alignment: .leading, spacing: /*@START_MENU_TOKEN@*/nil/*@END_MENU_TOKEN@*/, content: {
            Image(uiImage: httpRequests.currentImage!)
                .resizable()
                .scaledToFit()
            
            List (httpRequests.detectionList, id: \.self) { imageName in
                Button(action: {httpRequests.getImage(name: imageName)}, label: {
                    Text(imageName)
                })
            }
        })
    }
}

struct DetectionView_Previews: PreviewProvider {
    static var previews: some View {
        DetectionView()
    }
}
