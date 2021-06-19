//
//  DetectionView.swift
//  SmartCam
//
//  Created by Jasson Rodríguez Méndez on 18/6/21.
//

import SwiftUI

struct DetectionView: View {
    @StateObject var httpRequest = RequestManager()
    var body: some View {
        List (httpRequest.detectionList, id: \.self) { imageName in
            Text(imageName)
        }
    }
}

struct DetectionView_Previews: PreviewProvider {
    static var previews: some View {
        DetectionView()
    }
}
